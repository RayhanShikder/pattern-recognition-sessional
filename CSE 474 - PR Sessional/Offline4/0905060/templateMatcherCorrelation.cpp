#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<cmath>

using namespace std;


#define ref_width 400
#define ref_height 400
#define temp_width 100
#define temp_height 100



struct RGBType {
	double r;
	double g;
	double b;
};



vector<RGBType> readBMPColor(char* filename)
{
    vector<RGBType>res;

    int i,j;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    vector<double>gray;


    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);


    gray.resize(size/3);
    res.resize(size/3);

    for(i = 0,j=0; i < size; i += 3,j++)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
            //gray[j]=0.2989 * (double)data[i] + 0.5870 * (double)data[i+1] + 0.1140 * (double)data[i+2];
            res[j].r=(double)data[i];
            res[j].g=(double)data[i+1];
            res[j].b=(double)data[i+2];

    }

    return res;
}



vector<double> readBMP(char* filename)
{
    int i,j;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    vector<double>gray;


    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);


    gray.resize(size/3);
    for(i = 0,j=0; i < size; i += 3,j++)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
            gray[j]=0.2989 * (double)data[i] + 0.5870 * (double)data[i+1] + 0.1140 * (double)data[i+2];
            //gray[j]=0.3 * (double)data[i] + 0.59 * (double)data[i+1] + 0.11 * (double)data[i+2];


    }

    return gray;
}

void savebmp (const char *filename, int w, int h, int dpi, vector<RGBType> data) {
	FILE *f;
	int k = w*h;
	int s = 4*k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>>8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w>>8);
	bmpinfoheader[ 6] = (unsigned char)(w>>16);
	bmpinfoheader[ 7] = (unsigned char)(w>>24);

	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);

	f = fopen(filename,"wb");

	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);

	for (int i = 0; i < k; i++) {
		RGBType rgb = data[i];

		double red = (data[i].r);
		double green = (data[i].g);
		double blue = (data[i].b);

		unsigned char color[3] = {(char)floor(blue),(char)floor(green),(char)floor(red)};

		fwrite(color,1,3,f);
	}

	fclose(f);
}



int main()
{
    vector<double>ref_img;
    vector<double>temp_img;

    vector<RGBType>outputImage;


    temp_img=readBMP("clipped.bmp");
    ref_img=readBMP("test.bmp");

    outputImage=readBMPColor("test.bmp");


    double max_diff = -1.0,max,r,t;
    int min_i=-1,min_j=-1;

    cout<<"sizes "<<ref_img.size()<<" "<<temp_img.size()<<" "<<temp_width<<" "<<temp_height<<endl;

    for(int i=0;i<ref_height-temp_height ;i++)//reference image
    {
        for(int j=0;j<ref_width-temp_width;j++)
        {
            max=0.0;
            r=0.0;
            t=0.0;

            for(int k=0;k<temp_width;k++)//template image
            {
                for(int l=0;l<temp_height;l++)
                {
                    //int val=1;
                    double val1 = ref_img[((i+l)*ref_width)+(j+k)] ;
                    double val2 = temp_img[(l*temp_width)+k];

                    double val=(val1* val2);

                    max+=(double)val;
                    r+=(val1*val1);
                    t+=(val2*val2);


                }
            }
            max=(max/sqrt(r*t));
            if(max>max_diff)
            {
                max_diff=max;
                min_i=i;
                min_j=j;
            }
        }
    }



    for(int i=0;i<temp_height;i++)
    {
        for(int j=0;j<temp_width;j++)
        {


            outputImage[((i+min_i)*ref_width)+(j+min_j)].r=255.0;
            outputImage[((i+min_i)*ref_width)+(j+min_j)].g=255.0;
            outputImage[((i+min_i)*ref_width)+(j+min_j)].b=255.0;
        }
    }

    savebmp("output_correlation.bmp",ref_width,ref_height,24,outputImage);

    cout<<"Match found with "<<"diff "<<max_diff<<" index "<<min_i<<" "<<min_j<<endl;
    return 0;
}
