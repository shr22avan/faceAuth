#include <iostream>
#include <string>
#include <vector>
#include <stack>
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

#ifndef IMAGE_FILE_EXTENSION
#define IMAGE_FILE_EXTENSION "jpg"
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

string to_string (int a) {

	stack <int> st;
	do {
		st.push( a % 10 );
		a /= 10;
	}
	while(a);
	string b = "";
	while( ! st.empty() ){ 
		b += (st.top() + '0');
		st.pop();
	}

}

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
			path q(IMAGE_DIRECTORY_PATH);
			if( ! exists(q) ) {
				e.set_msg(*(new string("Invalid Location. There is no image repository here.")));
				throw e;
			}
			path p(IMAGE_DIRECTORY_PATH + username), r(img);
			if( ! exists(p) ) {
				create_directory(p);		
			}

			directory_iterator end_iter, start_iter(p);
			vector<path> image_paths;
			
			//Getting the paths of all the images corresponding to the given username.
			while(start_iter != end_iter) {
				image_paths.push_back(start_iter->path());	
				start_iter++;
			}
			
			//Copying the new image to the images repository
			string destination = IMAGE_DIRECTORY_PATH + username + "/" + to_string(image_paths.size() + 1) + "." + IMAGE_FILE_EXTENSION;
			path s(destination);
			copy_file(r, s); 

			//deleting the old file - commented out because, it maybe needed in the UI.
			//remove(r);
			image_paths.push_back(s);

			//Rebuild the CSV file:
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
