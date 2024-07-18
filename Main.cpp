#include "DfsMaze.h"
using namespace std;

void tDfs() {
	DfsMaze* dm = new DfsMaze;
#if !debug
	dm->show();
#endif
	string str;
	vector<string> command = { "flush","resize","decrypt","play"};

	while (cin) {
		for (int i = 0; i < command.size(); ++i) {
			cout << command[i] << "  ";
		}
		cout << "\n>>>" << flush;
		cin >> str;
		if (str == command[0]) {
			dm->flush();
			dm->show();
		}
		else if (str == command[1]) {
			delete dm;
			int height, width;
			cout << "height:";
			cin >> height;
			cout << "width:";
			cin >> width;
			dm = new DfsMaze(height, width);
			dm->show();
		}
		else if (str == command[2]) {
			dm->decrypt();
		}
		else if (str == command[3]) {
			dm->play();
		}
	}
	cin.clear();
	delete dm;
}

int main() {
	tDfs();


	return 0;
}