#pragma once

#include <tuple>
#include <memory>
#include <typeindex>

enum class TestType
{
	NONE = -1,
	CREATE_EMPTY_SCENE,
	LOAD_SCENE,
};


template<typename ...ARGS>
class ParameterARGS
{
public:
	ParameterARGS(ARGS... args) :
		ParametersTuple(std::make_tuple(args...))
	{
	}
	std::tuple<ARGS...> ParametersTuple;
};

struct Any
{
	Any(void) : m_tpIndex(std::type_index(typeid(void))) {}
	Any(const Any& that) : m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex) {}
	Any(Any && that) : m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex) {}
	//��������ָ��ʱ������һ������ͣ�ͨ��std::decay���Ƴ����ú�cv�����Ӷ���ȡԭʼ����
	template<typename U, class = typename std::enable_if<!std::is_same<typename  std::decay<U>::type, Any>::value, U>::type> Any(U && value)
		: m_ptr(new Derived < typename  std::decay<U>::type>(std::forward<U>(value))),
		m_tpIndex(std::type_index(typeid(typename std::decay<U>::type)))
	{
	}
	bool IsNull() const { return !bool(m_ptr); }
	template<class U> bool Is() const
	{
		return m_tpIndex == std::type_index(typeid(U));
	}
	//��Anyת��Ϊʵ�ʵ�����
	template<class U>
	U& AnyCast()
	{
		if (!Is<U>())
		{
			printf("can not cast %s to %s\n", typeid(U).name(), m_tpIndex.name());
		}
		auto derived = dynamic_cast<Derived<U>*> (m_ptr.get());
		return derived->m_value;
	}
	Any& operator=(const Any& a)
	{
		if (m_ptr == a.m_ptr)
			return *this;
		m_ptr = a.Clone();
		m_tpIndex = a.m_tpIndex;
		return *this;
	}
private:
	struct Base;
	typedef std::unique_ptr<Base> BasePtr;
	struct Base
	{
		virtual ~Base() {}
		virtual BasePtr Clone() const = 0;
	};
	template<typename T>
	struct Derived : Base
	{
		template<typename U>
		Derived(U && value) : m_value(std::forward<U>(value)) { }
		BasePtr Clone() const
		{
			return BasePtr(new Derived<T>(m_value));
		}
		T m_value;
	};
	BasePtr Clone() const
	{
		if (m_ptr != nullptr)
			return m_ptr->Clone();
		return nullptr;
	}
	BasePtr m_ptr;
	std::type_index m_tpIndex;
};

class ObjectFunctionBase
{

public:
	ObjectFunctionBase(TestType typeIndex) : TypeIndex(typeIndex) { }
	virtual ~ObjectFunctionBase() { }
	virtual void run(Any Parameters) = 0;

	TestType TypeIndex;
};

// ����ָ��
template <class Class, class Func, typename ...ARGS>
class ObjectFunctionPointer : public ObjectFunctionBase
{
public:
	ObjectFunctionPointer(TestType typeIndex, Class* object, Func func) :
		ObjectFunctionBase(typeIndex),
		Object(object),
		Function(func)
	{
	}
	virtual ~ObjectFunctionPointer() {}

	virtual void run(Any Parameters) override
	{
		auto _ParametersTuple = Parameters.AnyCast<ParameterARGS<ARGS...>>().ParametersTuple;
		invoke(_ParametersTuple);
	}

private:
	template<typename Tuple, std::size_t... Index>
	decltype(auto) invokeImpl(Tuple&& t, std::index_sequence<Index...>)
	{
		return (Object->*Function)(std::get<Index>(std::forward<Tuple>(t))...);
	}

	template<typename Tuple>
	decltype(auto) invoke(Tuple&& t)
	{
		constexpr auto size = std::tuple_size<typename std::decay<Tuple>::type>::value;
		return invokeImpl(std::forward<Tuple>(t), std::make_index_sequence<size>{});
	}

private:
	Class* Object;
	Func Function;
};