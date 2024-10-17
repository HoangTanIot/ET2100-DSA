// Bài 1: Nhập vào n đối tượng có màu đỏ (red), trắng (white) và xanh (blue), sắp xếp theo trật tự như sau:
// các đối tượng cùng màu nằm kế tiếp nhau và theo thứ tự đỏ, trắng, xanh.
// Input {xanh, đỏ, xanh, đỏ, đỏ, trắng, đỏ, xanh, trắng}
// Output {đỏ, đỏ, đỏ, đỏ, trắng, trắng, xanh, xanh, xanh}
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> sortColors(vector<string> colors) {
    unordered_map<string, int> colorMap;
    colorMap["đỏ"] = 0;
    colorMap["trắng"] = 1;
    colorMap["xanh"] = 2;

    int colorCounts[3] = {0, 0, 0};
    for (vector<string>::iterator it = colors.begin(); it != colors.end(); ++it) {
        colorCounts[colorMap[*it]]++;
    }
    vector<string> output;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < colorCounts[i]; j++) {
            if (i == 0) output.push_back("đỏ");
            else if (i == 1) output.push_back("trắng");
            else output.push_back("xanh");
        }
    }
    return output;
}

int main() {
    vector<string> inputColors;
    inputColors.push_back("xanh");
    inputColors.push_back("đỏ");
    inputColors.push_back("xanh");
    inputColors.push_back("đỏ");
    inputColors.push_back("đỏ");
    inputColors.push_back("trắng");
    inputColors.push_back("đỏ");
    inputColors.push_back("xanh");
    inputColors.push_back("trắng");

    vector<string> outputColors = sortColors(inputColors);
    for (vector<string>::iterator it = outputColors.begin(); it != outputColors.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}