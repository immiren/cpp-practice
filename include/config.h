const int cellCount = 9;

int getCellCount() {
	return cellCount;
}

struct NumberGrid {
	int arr[cellCount][cellCount];
};

NumberGrid getArray()
{
    NumberGrid var;
    for (int i = 0; i < cellCount; ++i) {
        for (int j = 0; j < cellCount; ++j) {
            var.arr[i][j] = i + j;
        }
    }
    return var;
}


//void printArray(Grid var)
//{
//    for (int i = 0; i < cellCount; ++i) {
//        for (int j = 0; j < cellCount; ++j) {
//            cout << var.arr[i][j] << " ";
//        }
//        cout << endl;
//    }
//}