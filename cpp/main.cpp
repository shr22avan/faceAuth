#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>

#include <sys/stat.h>
#include <iterator>
#include <boost/filesystem.hpp>

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#ifndef CSV_PATH 
#define CSV_PATH "./images.csv" 
#endif

#ifndef IMAGE_DIRECTORY_PATH
#define IMAGE_DIRECTORY_PATH "./images/"
#endif

#ifndef IMAGE_FILE_EXTENSION
#define IMAGE_FILE_EXTENSION "jpg"
#endif

using namespace std;
using namespace boost::filesystem;
using namespace cv;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if(!path.empty() && !classlabel.empty()) {
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}

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
		Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
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

			//deleting the old file - commented out because, those images maybe needed in the UI.
			//remove(r);
			image_paths.push_back(s);

			//Build the CSV file:
			system("python csv_create.py images");

		}
		else if(action == "detect") {
			
			vector<Mat> images;
			vector<int> labels;
			
			read_csv(CSV_PATH, images, labels);
			
			if(images.size() <= 1) {
				string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
				CV_Error(CV_StsError, error_message);
			}
			
			model->train(images, labels);

			/* Need Username and the test image */
			
			if(argc != 4) {
				e.set_msg(*(new string("Invalid Arguments. Usage: face_recognizer detect <username> <test_image_location>")));
				throw e;
			}

			string uname = argv[2], img = argv[3];
			path i(*(new string(img)));

			int predictedLabel = model -> predict(imread(img, 0));
			cout << predictedLabel << endl;

		}
		else {
			e.set_msg(*(new string("Unknown command use either add or detect")));
			throw e;
		}
	}
	catch (s_exception t) {

		cerr << t.get_msg() << endl;
		return 1;

	}
	catch (cv::Exception& r) {
		cerr << "Error opening file \"" << CSV_PATH << "\". Reason: " << r.msg << endl;
		// nothing more we can do
		exit(1);
	}
	return 0;
}
