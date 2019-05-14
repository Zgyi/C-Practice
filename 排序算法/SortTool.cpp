#include "pch.h"
#include "SortTool.h"

void bubbleSort(std::vector<int>& arrays, int size)
{
	for (int i = 0; i < size; i++)
	{
		bool exchange = false;
		for (int j = 0; j < size - 1; j++)
		{
			if (arrays[j + 1] < arrays[j])
			{
				int temp = arrays[j];
				arrays[j] = arrays[j + 1];
				arrays[j + 1] = temp;

				exchange = true;
			}
		}

		if (exchange == false)
		{
			return;
		}
	}
}

void quickSort(std::vector<int>& arrays, int low, int high)
{
	if (low < high)
	{
		int lowTemp = low;
		int highTemp = high;
		int firstElement = arrays[low];

		while (low < high)
		{
			while (low < high && arrays[high] > firstElement)
			{
				high--;
			}
			arrays[low] = arrays[high];

			while (low < high && arrays[low] <= firstElement)
			{
				low++;
			}
			arrays[high] = arrays[low];
		}

		arrays[low] = firstElement;
		quickSort(arrays, lowTemp, low - 1);
		quickSort(arrays, high + 1, highTemp);
	}
}

void headSort(std::vector<int>& arrays, int size)
{
	// 1.�����󶥶ѣ��ӵ�һ����Ҷ�ӽڵ�������ϣ�arrays[size / 2 - 1]�ǵ�һ����Ҷ�ӽڵ�
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		adjustHeap(arrays, i, size);
	}

	// 2. �����ѽṹ + �����Ѷ�Ԫ��
	for (int i = size - 1; i > 0; i--)
	{
		int temp = arrays[0];
		arrays[0] = arrays[i];
		arrays[i] = temp;

		adjustHeap(arrays, 0, i);
	}
}

void adjustHeap(std::vector<int>& arrays, int index, int size)
{
	// ��¼��Ҷ�ӽڵ��ֵ
	int temp = arrays[index];
	// ���ʸ÷�Ҷ�ӽڵ�����Һ��ӣ�index * 2 + 1�����ӣ�i * 2 + 1�� i ����/�Һ��ӣ�Ĭ�������ӣ��������ִ����i++�����Һ���
	for (int i = index * 2 + 1; i < size; i = i * 2 + 1)
	{
		// �ж����Һ���˭�󣬽��������ֵ
		if (i + 1 < size && arrays[i] < arrays[i + 1])
		{
			// ʹ���Һ��ӣ���������Һ��ӵ�����
			i++;
		}
		// �������û�нṹ�ı��break����������˸ı䣬���²�ĺ��Ӹ���ֵ
		if (arrays[i] > temp)
		{
			arrays[index] = arrays[i];
			index = i;
		}
		else
		{
			break;
		}
	}
	// ����ֵ
	arrays[index] = temp;
}
