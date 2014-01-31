#include <iostream>
#include <string>
#include <sys/stat.h>
#include <iterator>
#include <boost/filesystem.hpp>


#ifndef CSV_NAME
#define CSV_NAME images.csv
#endif

#ifndef CSV_PATH 
#define CSV_PATH "./" 
#endif

#ifndef IMAGE_DIRECTORY_PATH
#define IMAGE_DIRECTORY_PATH "./images/"
#endif
using namespace std;
using namespace boost::filesystem;

struct s_exception {
	
	private:
	string msg;

	public:
	
	void set_msg(string e) {
		msg = e;
	}

	string get_msg() {
		return msg;
	}

} e;


int main(int argc, char *argv[]) {
	try {
		if(argc < 3) {
			e.set_msg(*(new string("Usage: face_recognizer <action_parameter> <value_parameter_list>")));
			throw e;
		}
		string action = argv[1], value = argv[2];
		if(action == "add") {
			/* Need Username and the current image location */
			if(argc != 4) {
				e.set_msg(*(new string("Invalid Arguments. Usage: face_recognizer add <username> <image_location>")));
				throw e;
			}
			string username = argv[2], img = argv[3];
			path p(IMAGE_DIRECTORY_PATH + username);
			if( ! exists(p) ) {
			}
		}
		else if(action == "detect") {
			/* Need Username and the test image */
			if(argc != 4) {
				e.set_msg(*(new string("Invalid Arguments. Usage: face_recognizer detect <username> <test_image_location>")));
				throw e;
			}
		}
		else {
			;
		}
	}
	catch (s_exception t) {
		cerr << t.get_msg() << endl;
		return 1;
	}
	return 0;
}
