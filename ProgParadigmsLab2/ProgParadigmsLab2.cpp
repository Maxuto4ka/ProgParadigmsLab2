#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

class RandomPermutation {
public:
    RandomPermutation(int n) : n_(n), sequence_(n) {
        for (int i = 0; i < n; ++i) {
            sequence_[i] = i + 1;
        }
        random_device rd;
        mt19937 g(rd());
        shuffle(sequence_.begin(), sequence_.end(), g);
    }

    void Print() {
        for (int i : sequence_) {
            cout << i << " ";
        }
        cout << endl;
        vector<int> seriesLengths;
        int currentLength = 1;
        for (int i = 1; i < n_; ++i) {
            if (sequence_[i] > sequence_[i - 1]) {
                currentLength++;
            }
            else {
                seriesLengths.push_back(currentLength);
                currentLength = 1;
            }
        }
        seriesLengths.push_back(currentLength);

        cout << "Series: ";
        for (int length : seriesLengths) {
            cout << length << " ";
        }
        cout << endl;
    }

    vector<int> operator()() {
        vector<int> seriesLengths;
        int currentLength = 1;
        for (int i = 1; i < n_; ++i) {
            if (sequence_[i] > sequence_[i - 1]) {
                currentLength++;
            }
            else {
                seriesLengths.push_back(currentLength);
                currentLength = 1;
            }
        }
        seriesLengths.push_back(currentLength);
        return seriesLengths;
    }

private:
    int n_;
    vector<int> sequence_;
};

int main() {
    int numberOfPermutations = 1000;
    int const n = 100;
    int numberOfSeriesWithLength[n];
    for (int i = 0; i < n; ++i) {
        numberOfSeriesWithLength[i] = 0;
    }

    for (int i = 0; i < numberOfPermutations; ++i) {
        RandomPermutation permutation(n);
        //permutation.Print();
        vector<int> seriesLengths = permutation();
        for (int length : seriesLengths) {
            numberOfSeriesWithLength[length - 1]++;
        }
    }

    int maxLength = 0;
    for (int i = 0; i < n; ++i) {
        if (numberOfSeriesWithLength[i] > 0) maxLength = i + 1;
    }
    double sumSeries = 0;
    for (int i = 0; i < maxLength; ++i) {
        sumSeries += numberOfSeriesWithLength[i];
    }
    int zeroTimes = 0;
    cout << "Series length : % among all serieses\n";
    for (int i = 1; i <= maxLength; ++i) {
        double percentage = static_cast<double>(numberOfSeriesWithLength[i - 1]) / sumSeries * 100.0;
        if (percentage != 0) {
            cout << i << " : " << percentage << "%\n";
        }
        else zeroTimes++;
    }

    int mostCommonLength = 1;
    for (int i = 1; i <= maxLength; ++i) {
        if (numberOfSeriesWithLength[i] > numberOfSeriesWithLength[i - 1]) mostCommonLength = i + 1;
    }
    int mostCommonLengthFrequency = numberOfSeriesWithLength[mostCommonLength - 1];

    double averageLength = (numberOfPermutations * n) / sumSeries;

    int dif = maxLength - zeroTimes;
    double* series = new double[maxLength];
    for (int i = 0; i < maxLength; ++i) {
        series[i] = i + 1;
    }
    for (int i = 0; i < maxLength; i++) {
        for (int j = i + 1; j < maxLength; j++) {
            if (numberOfSeriesWithLength[i] < numberOfSeriesWithLength[j]) {
                int temp = numberOfSeriesWithLength[j];
                numberOfSeriesWithLength[j] = numberOfSeriesWithLength[i];
                numberOfSeriesWithLength[i] = temp;
                int temp1 = series[j];
                series[j] = series[i];
                series[i] = temp1;
            }
        }
    }
    double median;
    if (dif % 2 == 0) {
        median = (series[(dif / 2) - 1] + series[(dif / 2)]) / 2;
    }
    else {
        median = series[(dif / 2)];
    }

    cout << "The most common length: " << mostCommonLength << " (Frequency: " << mostCommonLengthFrequency << " times)\n";
    cout << "Average length: " << averageLength << "\n";
    cout << "Median: " << median << "\n";

    delete[] series;

    return 0;
}
