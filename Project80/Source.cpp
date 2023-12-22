#include <iostream>
#include <vector>
#include <random>
#define SIZE 1000

using namespace std;

struct stats
{
    size_t comparison_count = 0;
    size_t copy_count = 0;

    friend stats operator+(const stats& left, const stats& right);
};

stats operator+(const stats& left, const stats& right)
{
    stats stats;
    stats.comparison_count = left.comparison_count + right.comparison_count;
    stats.copy_count = left.copy_count + right.copy_count;
    return stats;
}

vector<int> generate_sorted_vector(const int n)
{
    vector<int> result;
    for (int i = 0; i < n; ++i)
    {
        result.push_back(i);
    }
    return result;
}

vector<int> generate_inverted_vector(const int n)
{
    vector<int> result;
    for (int i = n - 1; i >= 0; --i)
    {
        result.push_back(i);
    }
    return result;
}

vector<int> generate_random_vector(const int n)
{
    vector<int> result;
    for (int i = 0; i < n; ++i)
    {
        result.push_back(rand() % n);
    }
    return result;
}

stats insertion_sort(std::vector<int>& arr)
{
    stats stats;

    size_t length = arr.size();
    for (size_t i = 1; i < length; i++)
    {
        int key = arr[i];
        size_t j = i;

        while (j > 0 && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            j--;
            stats.copy_count += 1;
            stats.comparison_count += 1;
        }

        arr[j] = key;
        stats.copy_count += 1;
    }

    return stats;
}

stats shaker_sort(std::vector<int>& arr)
{
    stats stats;
    int left = 0, right = arr.size() - 1;

    while (left <= right)
    {
        for (int i = left; i < right; i++)
        {
            stats.comparison_count += 1;
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                stats.copy_count += 1;
            }
        }
        right--;

        for (int i = right; i > left; i--)
        {
            stats.comparison_count += 1;
            if (arr[i - 1] > arr[i])
            {
                swap(arr[i - 1], arr[i]);
                stats.copy_count += 1;
            }
        }
        left++;
    }

    return stats;
}

void merge(std::vector<int>& arr, int l, int m, int r, stats& stats)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2)
    {
        stats.comparison_count += 1;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        stats.copy_count += 1;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        stats.copy_count += 1;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        stats.copy_count += 1;
    }
}

stats merge_sort(std::vector<int>& arr, int l, int r)
{
    stats stats;

    if (l < r)
    {
        int m = l + (r - l) / 2;

        stats = merge_sort(arr, l, m);
        stats = stats + merge_sort(arr, m + 1, r);

        merge(arr, l, m, r, stats);
    }

    return stats;
}

int main()
{
    vector<int> vector_testing1{ 0, 1, 553, 522, 4, 52, 8 };
    vector<int> vector_testing2{ 0, 1, 553, 522, 4, 52, 8 };
    vector<int> vector_testing3{ 0, 1, 553, 522, 4, 52, 8 };
    insertion_sort(vector_testing1);
    shaker_sort(vector_testing2);
    merge_sort(vector_testing3, 0, vector_testing3.size() - 1);

    for (int i = 0; i < vector_testing1.size(); ++i) {
        cout << vector_testing1[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < vector_testing2.size(); ++i) {
        cout << vector_testing2[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < vector_testing3.size(); ++i) {
        cout << vector_testing3[i] << " ";
    }
    cout << "\n";

    vector<int> vector;
    cout << "------SORTED ARRAY------" << endl;

    size_t sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_sorted_vector(SIZE);
        stats tmp;
        tmp = insertion_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Insertion sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        srand(i);
        vector = generate_sorted_vector(SIZE);
        stats tmp = shaker_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Shaker sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        srand(i);
        vector = generate_sorted_vector(SIZE);
        stats tmp = merge_sort(vector, 0, vector.size() - 1);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Merge sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    cout << "------INVERTED ARRAY------" << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_inverted_vector(SIZE);
        stats tmp = insertion_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Insertion sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_inverted_vector(SIZE);
        stats tmp = shaker_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Shaker sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_inverted_vector(SIZE);
        stats tmp = merge_sort(vector, 0, vector.size() - 1);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Merge sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;


    cout << "------RANDOM ARRAY------" << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_random_vector(SIZE);
        stats tmp = insertion_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Insertion sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_random_vector(SIZE);
        stats tmp = shaker_sort(vector);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Shaker sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    sum_copy = 0, sum_comparison = 0;
    for (int i = 0; i < 100; ++i) {
        vector = generate_random_vector(SIZE);
        stats tmp = merge_sort(vector, 0, vector.size() - 1);
        sum_copy += tmp.copy_count;
        sum_comparison += tmp.comparison_count;
    }
    cout << "Sort: Merge sort\nSize array: " << SIZE << "\nAverage copy count: " << sum_copy / 100
        << "\nAverage comparison count: " << sum_comparison / 100 << endl << endl;

    return 0;
}