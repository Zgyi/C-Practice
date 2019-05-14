#pragma once

#include <vector>

/*
	�����㷨
*/

// һ���ð��������ƽ��ʱ�临�Ӷ�Ϊ O(n^2)���ȶ�
// ð���Ż���
void bubbleSort(std::vector<int>& arrays, int size);

// �������ʱ��Ϊ O(n^2)��ƽ��ʱ�临��Ϊ O(n * log2 N)�����ȶ�
// ����
void quickSort(std::vector<int>& arrays, int low, int high);


// ����������ƽ������ O(n * log2 N)�����ȶ�
// ������
void headSort(std::vector<int>& arrays, int size);
// ����
void adjustHeap(std::vector<int>& arrays, int index, int size);
