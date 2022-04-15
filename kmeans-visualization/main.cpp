#include "render.h"
#include <string>
#include "text.h"
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <SDL2/SDL_image.h>
#include <armadillo>
using namespace std;
typedef std::vector<double> stdvec;
typedef std::vector< std::vector<double> > stdvecvec;

stdvecvec mat_to_std_vec(arma::mat &A) {
    stdvecvec V(A.n_cols);
    for (size_t i = 0; i < A.n_cols; ++i) {
        V[i] = arma::conv_to< stdvec >::from(A.row(i));
    };
    return V;
}

int lastFrame, frameCount;

struct getpix{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int getIndex(vector<double> v, double K) {
    auto it = find(v.begin(), v.end(), K);
    if (it != v.end()) {
        int index = it - v.begin();
        return index;
    }
    return 0;
}

double dis(vector<double> vect1, vector<double> vect2) {
    return double(sqrt(pow((vect1[0] - vect2[0]), 2) + pow((vect1[1] - vect2[1]), 2)));
} 

void putpixel(SDL_Surface* screen, SDL_Surface *f, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    Uint32* pixels = (Uint32*)screen->pixels;
    Uint32* pixel = pixels + y*screen->pitch/4 + x;
    *pixel = SDL_MapRGB(f->format,r,g,b);
}
int main(int argc, char *argv[]) {
    
    render window("v2.1", 1200 , 700);
    SDL_StartTextInput();
        //cout << inImage->h << " " << inImage->w << endl;
        //SDL_LockSurface(inImage);
        //SDL_Color p[inImage->w * inImage->h];
        //uint32_t pixel = *( ( uint32_t * )inImage->pixels + 0 * inImage->w + 0 ) ;
        //SDL_GetRGB(pixel, inImage->format, &p[tmp].r, &p[tmp].g, &p[tmp].b);
        



    int frame = 0;
    int count = 0;
    // menu
    //SDL_Texture *logo = window.loadTexture("img/techs2.jpg");
    SDL_Rect option_1 = {115, 400, 250, 50};
    SDL_Rect option_2 = {730, 400, 350, 50};
    SDL_Rect intro = {92, 136, 0, 0};
    SDL_Rect vis = {120, 415, 0, 0};
    SDL_Rect imgc = {738, 415, 0, 0};

    // img

    SDL_Rect type_tex = {50, 510, 0, 0};
    SDL_Rect reset_tex = {447, 512, 0, 0};
    SDL_Rect input_1_tex = {257, 512, 0, 0};
    SDL_Rect cv_tex = {1035, 512, 0, 0};
    SDL_Rect input_k_tex = {700 + 5, 512, 0, 0};
    SDL_Rect input_2_tex = {843, 512, 0, 0};
    SDL_Rect output_img_tex = {425, 630, 0, 0};
    SDL_Rect save_tex = {628, 632, 0, 0};
    


    //window.rendering(logo, &logosrc, &logodst);
    // panel    
    SDL_Rect panel_1 = {10, 10, 1180, 600};
    SDL_Rect panel_2 = {11, 11, 1178, 598};

    // K
    SDL_Rect K_1 = {50, 640, 30, 30};
    SDL_Rect K_2 = {82, 640, 96, 30};
    SDL_Rect K_3 = {180, 640, 30, 30};
    SDL_Rect K_b = {83, 641, 94, 28};


    
    // Run
    SDL_Rect run_b = {180 + 30 + 50, 640, 80, 30};
    SDL_Rect run = {180 + 30 + 50 + 1, 641, 78, 28};
    
    // random
    SDL_Rect rdm_b = {390, 640, 110, 30};
    SDL_Rect rdm = {390 + 1, 641, 108, 28};
    
    // number of p
    SDL_Rect p1_b = {550, 620, 180, 40};
    SDL_Rect p1 = {550 + 1, 621, 180 - 2, 40 - 2};
    SDL_Rect p2_b = {710, 620, 110, 40};
    SDL_Rect p2 = {711, 621, 110 - 2, 40 - 2};
    
    // error
    int temp = 35;
    int temp_y = 620 + 35;
    SDL_Rect e1_b = {550, temp_y, 180, temp};
    SDL_Rect e1 = {550 + 1, temp_y + 1, 180 - 2, temp - 2};
    SDL_Rect e2_b = {710, temp_y, 110, temp};
    SDL_Rect e2 = {711, temp_y + 1, 110 - 2, temp - 2};

    // algorithm
    SDL_Rect a1_b = {870, 640, 150, 30};
    SDL_Rect a1 = {870 + 1, 641, 150 - 2, 28};
    
    // reset
    SDL_Rect rs1_b = {1070, 640, 80, 30};
    SDL_Rect rs1 = {1070 + 1, 641, 80 - 2, 28};


    TTF_Init();
    text texPos;
    texPos.setFont("font/NotoSansMono-Bold.ttf", 16);
    SDL_Color texPos_color = {42, 161, 152};

    // K
    text _k1;
    _k1.setFont("font/NotoSansMono-Bold.ttf", 25);
    SDL_Color _k1_color = {255, 255, 255};
    SDL_Rect _k1_rect = {57, 635, 0, 0};

    text _k2;
    _k2.setFont("font/NotoSansMono-Bold.ttf", 25);
    SDL_Color _k2_color = {255, 255, 255};
    SDL_Rect _k2_rect = {184 + 3, 647 + 3 - 12, 0, 0};

    // run
    text _run;
    _run.setFont("font/Sans.ttf", 25);
    SDL_Color _run_color = {255, 255, 255};
    SDL_Rect _run_rect = {184 + 84 + 5, 647 - 10, 0, 0};

    // random
    text _random;
    _random.setFont("font/Sans.ttf", 23);
    SDL_Color _random_color = {255, 255, 255};
    SDL_Rect _random_rect = {184 + 84 + 84 + 43, 647 - 8, 0, 0};

    // points
    text _points;
    _points.setFont("font/Sans.ttf", 15);
    SDL_Color _points_color = {255, 255, 255};
    SDL_Rect _points_rect = {555 + 5, 630 - 3, 0, 0};

    // error
    text _error;
    _error.setFont("font/Sans.ttf", 15);
    SDL_Color _error_color = {255, 255, 255};
    SDL_Rect _error_rect = {590 + 10, 665 - 4, 0, 0};
    // algorithm
    text _algorithm;
    _algorithm.setFont("font/Sans.ttf", 18);
    SDL_Color _algorithm_color = {255, 255, 255};
    SDL_Rect _algorithm_rect = {870 + 10, 647 - 5, 0, 0};
    // reset +
    text _reset;
    _reset.setFont("font/Sans.ttf", 18);
    SDL_Color _reset_color = {255, 255, 255};
    SDL_Rect _reset_rect = {1085 - 1, 647 - 5, 0, 0};
    // error
    text ERROR;
    int error = 0;
    ERROR.setFont("font/Sans.ttf", 20);
    SDL_Color er = {255, 255, 255};
    SDL_Rect error_rect = {740, 660 - 5, 0, 0};
    // number of points
    
    text menuText;
    menuText.setFont("font/JosefinSans-Regular.ttf", 30);
    text img_tex;
    img_tex.setFont("font/JosefinSans-Regular.ttf", 15);
    
    // img
    SDL_Rect img_input = {15, 50, 550, 400};
    SDL_Rect img_output = {1200 - 15 - 550, 50, 550, 400};
    SDL_Rect text_intput_back = {30 - 1, 500 - 1, 200 + 2, 40 + 2};
    SDL_Rect text_input = {30, 500, 200, 40};
    SDL_Rect reset_back = {425 - 1, 500 - 1, 100 + 2, 40 + 2};
    SDL_Rect reset = {425, 500, 100, 40};
    SDL_Rect input_back = {240 - 1, 500 - 1, 80 + 2, 40 + 2};
    SDL_Rect input_bot = {240, 500, 80, 40};
    SDL_Rect cv_back = {1200 - 100 - 100 - 1, 500 - 1, 150 + 2, 40 + 2};
    SDL_Rect cv = {1200 - 100 - 100, 500, 150, 40};
    SDL_Rect input_k_back = {666 - 1, 500 - 1, 150 + 2, 40 + 2};
    SDL_Rect input_k = {666, 500, 150, 40};
    SDL_Rect input_back_2 = {666 + 150 + 10 - 1, 500 - 1, 80 + 2, 40 + 2};
    SDL_Rect input_2 = {666 + 150 + 10, 500, 80, 40};
    SDL_Rect img_save_back = {400 - 1, 620 - 1, 200 + 2, 40 + 2};
    SDL_Rect img_save = {400, 620, 200, 40};
    SDL_Rect save_back = {400 + 200 + 10 - 1, 620 - 1, 80 + 2, 40 + 2};
    SDL_Rect save = {400 + 200 + 10, 620, 80, 40};

    
    bool type_image_name = 0;
    bool type_K_value = 0;
    bool K_value_inputted = 0;
    bool image_inputted = 0;
    bool image_converted = 0;
    string image_name = "";
    string K_tex_int = "";
    int K_in = 0;
    int a_img_in = 0;
    int b_img_in = 0;
    int img_in_x_pos = 15;
    int img_in_y_pos = 0;
    int img2_y_pos = 0;
    int img2_x_pos = 1200 - 15 - 550;
    SDL_Texture *outImageTex;
    SDL_Surface *outImageSurf;
    SDL_Surface *inImage;

    SDL_Color random_color[8];
    random_color[0] = {220, 50, 47};
    random_color[1] = {133, 153, 0};
    random_color[2] = {38, 139, 210};
    random_color[3] = {181, 137, 0};
    random_color[4] = {108, 113, 196};
    random_color[5] = {147, 161, 161};
    random_color[6] = {225, 225, 225};
    random_color[7] = {0, 0, 0};

    vector<vector<double>> points;
    vector<vector<double>> clusters;
    vector<double> labels;
    int K = 0;
    SDL_Event event;
    int mouse_x, mouse_y;
while(window.isRunning) {
    lastFrame = SDL_GetTicks();
    static int lastTime;
    if (lastFrame >= (lastTime+1000)) {
        lastTime = lastFrame;
        frameCount = 0;
        count++;
    }
   
    SDL_GetMouseState(&mouse_x, &mouse_y);

    while (window.menuisRunning) {
       
        window.fillRect(&option_1, 88, 110, 117);
        window.fillRect(&option_2, 88, 110, 117);
        menuText.setTex("KMEANS ALGORITHM VISUALIZATION AND IMAGE COMPRESSION", random_color[6], window.getRender());
        menuText.blitText(window.getRender(), &intro);
        menuText.setTex("VISUALIZATION", random_color[6], window.getRender());
        menuText.blitText(window.getRender(), &vis);
        menuText.setTex("IMAGE COMPRESSION", random_color[6], window.getRender());
        menuText.blitText(window.getRender(), &imgc);
        SDL_GetMouseState(&mouse_x, &mouse_y);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                cout << "Press Exit" << endl; 
                window.isRunning = false;
                window.menuisRunning = false;
                window.clear();
                window.cleanUp();
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if((115 < mouse_x && mouse_x < 365) && (400 < mouse_y && mouse_y < 450)) {
                    cout << "visualization mode" << endl;
                    window.kmeansisRunning = true;
                    window.menuisRunning = false;
                    window.imgcompressisRunning = false;
                }
                if ((730 < mouse_x && mouse_x < 1080) && (400 < mouse_y && mouse_y < 450)) {
                    cerr << "image compression mode" << endl;
                    window.imgcompressisRunning = true;
                    window.menuisRunning = false;
                    window.kmeansisRunning = false;
                }
            }
        }
        window.display();
        window.clear();
        //SDL_DestroyTexture(please);
    } // end while menu

    while (window.imgcompressisRunning) {

        


        SDL_GetMouseState(&mouse_x, &mouse_y);
        //cout << mouse_x << " " << mouse_y << endl;
        window.fillRect(&img_input, 0, 0, 0);
        window.fillRect(&img_output, 0, 0, 0);
        window.fillRect(&text_intput_back, 147, 161, 161);
        window.fillRect(&text_input, 0, 43, 54);
        window.fillRect(&reset_back, 147, 161, 161);
        window.fillRect(&reset, 0, 43, 54);
        window.fillRect(&input_back, 147, 161, 161);
        window.fillRect(&input_bot, 0, 43, 54);
        window.fillRect(&cv_back, 147, 161, 161);
        window.fillRect(&cv, 0, 43, 54);
        window.fillRect(&input_k_back, 147, 161, 161);
        window.fillRect(&input_k, 0, 43, 54);
        window.fillRect(&input_back_2, 147, 161, 161);
        window.fillRect(&input_2, 0, 43, 54);
        window.fillRect(&img_save_back, 147, 161, 161);
        window.fillRect(&img_save, 0, 43, 54);
        window.fillRect(&save_back, 147, 161, 161);
        window.fillRect(&save, 0, 43, 54);
       
        
        img_tex.setTex("RESET", random_color[6], window.getRender());
        img_tex.blitText(window.getRender(), &reset_tex);
        img_tex.setTex("INPUT", random_color[6], window.getRender());
        img_tex.blitText(window.getRender(), &input_1_tex);
        img_tex.setTex("CONVERT", random_color[6], window.getRender());
        img_tex.blitText(window.getRender(), &cv_tex);
        
        img_tex.setTex("INPUT", random_color[6], window.getRender());
        img_tex.blitText(window.getRender(), &input_2_tex);
        img_tex.setTex("Type image's name", random_color[6], window.getRender());
        img_tex.blitText(window.getRender(), &output_img_tex);
        img_tex.setTex("SAVE", random_color[6], window.getRender());
        img_tex.blitText(window.getRender(), &save_tex);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                cout << "Press Exit" << endl; 
                window.isRunning = false;
                window.imgcompressisRunning = false;
                window.clear();
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // image name input
                if ((30 < mouse_x && mouse_x < 30 + 200) && (500 < mouse_y && mouse_y < 540)) {
                    type_image_name = true;
                } else {
                    type_image_name = false;
                }
                // check image input or not
                if ((240 < mouse_x && mouse_x < 240 + 80) && (500 < mouse_y && mouse_y < 540)) {
                    image_inputted = 1;
                }
                // K input
                if ((666 < mouse_x && mouse_x < 666 + 150) && (500 < mouse_y && mouse_y < 540)) {
                    type_K_value = true;
                } else {
                    type_K_value = false;
                }
                if ((425 < mouse_x && mouse_x < 425 + 100) && (500 < mouse_y && mouse_y < 540)) {
                    image_name.clear();
                    K_tex_int.clear();
                    K_in = 0;
                    K_tex_int.clear();
                    type_image_name = false;
                    image_inputted = false;
                }
                if ((666 + 150 + 10 < mouse_x && mouse_x < 666 + 150 + 10 + 80) && (500 < mouse_y && mouse_y < 540)) {
                    K_in = stoi(K_tex_int);
                    K_value_inputted = true;
                    cerr << "K value found" << endl;
                }
                if ((1000 < mouse_x && mouse_x < 1000 + 150) && (500 < mouse_y && mouse_y < 540) && K_value_inputted == true) {
                    cerr << "begin compressing" << endl;
                    inImage = IMG_Load(image_name.c_str());
                    arma::mat data(3, inImage->w * inImage->h);
                    vector<vector<uint8_t>> vect(inImage->w * inImage->h);
                    SDL_LockSurface(inImage);
                    int tmp = 0;
                    for (int i = 0; i < inImage->h; i++) {
                        for (int j = 0; j < inImage->w; j++) {
                            uint8_t r = 0;
                            uint8_t g = 0;
                            uint8_t b = 0;
                            uint32_t pixel = *((uint32_t *)inImage->pixels + i * inImage->w + j);
                            SDL_GetRGB(pixel, inImage->format, &r, &g, &b);
                            vect[tmp].push_back(r);
                            vect[tmp].push_back(g);
                            vect[tmp].push_back(b);
                            data.col(tmp) = arma::vec({double(int(r)), double(int(g)), double(int(b))}); 
                            tmp++;
                        }
                    }
                    cout << (data.cols(0, 5)) << endl;
                    SDL_UnlockSurface(inImage);
                    arma::mat centroids;
                    arma::Row<size_t> labels;
                    mlpack::kmeans::KMeans<> mlkmeans;
                    mlkmeans.Cluster(data, K_in, labels, centroids);
                    //arma::kmeans(labels, data, K_in, arma::random_subset, 10, true);
                    centroids.print("Centroids:");
                    vector<vector<uint8_t>> outImage_rgb(inImage->w * inImage->h * 3);
                    for (int i = 0; i < inImage->w*inImage->h; i++) {
                        outImage_rgb[i].push_back(int((centroids.at(0, labels.at(i)))));
                        outImage_rgb[i].push_back(int((centroids.at(1, labels.at(i)))));
                        outImage_rgb[i].push_back(int((centroids.at(2, labels.at(i)))));
                    }
                    cout << int(outImage_rgb[0][0]) << " " << int(outImage_rgb[0][1]) << " " << int(outImage_rgb[0][2] )<< endl;
                    cout << int(outImage_rgb[1][0]) << " " << int(outImage_rgb[1][1]) << " " << int(outImage_rgb[1][2] )<< endl;
                    outImageSurf = SDL_CreateRGBSurface(inImage->flags, inImage->w, inImage->h, 32, 0, 0, 0, 0);
                    //cerr << outImage_rgb.size() << endl;
                    cerr << labels.at(0) << " " << labels.at(1) << " " << labels.at(2) << endl;
                    int iii = 0;
                    for (int i = 0; i < inImage->h; i++) {
                        for (int j = 0; j < inImage->w; j++) {
                            putpixel(outImageSurf, inImage, j, i, outImage_rgb[iii][2], outImage_rgb[iii][1], outImage_rgb[iii][0]);
                            iii++;
                        }
                    }               
                    
                    cerr << "Convert exc" << endl;
                    image_converted = true;
                    K_value_inputted = false;
                }
            }
            
            // input string and render
            if (type_image_name)  {
               if ( event.type == SDL_TEXTINPUT ) {
			image_name += event.text.text;
			cout << " > " << image_name << endl;
		} else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && image_name.size())  {
			image_name.pop_back();
			cout << " > " << image_name << endl;
		}
            }
            if (type_K_value)  {
               if ( event.type == SDL_TEXTINPUT ) {
			K_tex_int += event.text.text;
			cout << " > " << K_tex_int << endl;
		} else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && K_tex_int.size())  {
			K_tex_int.pop_back();
			cout << " > " << K_tex_int << endl;
		}
            }
         
        }
     
        if (type_image_name == 0) {
            img_tex.setTex("Type image's name here ...", random_color[6], window.getRender());
            img_tex.blitText(window.getRender(), &type_tex);
        } else {
            img_tex.setTex(image_name.c_str(), random_color[6], window.getRender());
            img_tex.blitText(window.getRender(), &type_tex);
        }
        if (type_K_value == 0) {
            img_tex.setTex("INPUT K", random_color[6], window.getRender());
            img_tex.blitText(window.getRender(), &input_k_tex);
        } else {
            img_tex.setTex(K_tex_int.c_str(), random_color[6], window.getRender());
            img_tex.blitText(window.getRender(), &input_k_tex);

        }

        if (image_inputted) {
            int width = 0;
            int height = 0;
            SDL_Texture *in = window.loadTexture(image_name.c_str());    
            SDL_QueryTexture(in, NULL, NULL, &width, &height);
            //cout << width << " " << height << endl;
            if (width > height) {
                a_img_in = 550;
                if (width < 500) b_img_in = int((width / 550) * height);
                if (width >= 500) b_img_in = int(float(500.0 / width*1.0) * height);
                img_in_y_pos = 50 + 400 - b_img_in;
                img2_y_pos = img_in_y_pos;
            }
            if (height >= width) {
                b_img_in = 400;
                if (height < 400) a_img_in = int((height / 400) * width);
                if (height >= 400) a_img_in = int(float(400.0 / height*1.0) * width);
                img_in_y_pos = 50;
                img2_y_pos = img_in_y_pos;
            }
            //cout << img_in_x_pos << " " << img_in_y_pos << endl;
            //cout << a_img_in << " " << b_img_in << endl;
            SDL_Rect imin_dst = {img_in_x_pos, img_in_y_pos, a_img_in, b_img_in};
            SDL_RenderCopy(window.getRender(), in, NULL, &imin_dst);
            SDL_DestroyTexture(in);
        }
        if (image_converted) {
            outImageTex = SDL_CreateTextureFromSurface(window.getRender(), outImageSurf);
            SDL_Rect outImageRect = {img2_x_pos, img2_y_pos, a_img_in, b_img_in};
            window.rendering(outImageTex, NULL, &outImageRect);
            SDL_DestroyTexture(outImageTex);
        }
        window.display();
        window.clear();



    } // end while image compression

    while (window.kmeansisRunning) {
        window.fillRect(&panel_1, 255, 255, 255);
        window.fillRect(&panel_2, 0, 20, 26);
        window.fillRect(&K_1, 88, 110, 117);
        window.fillRect(&K_2, 88, 110, 117);
        window.fillRect(&K_3, 88, 110, 117);
        window.fillRect(&K_b, 0, 20, 26);
        window.fillRect(&run_b, 255, 255, 255);
        window.fillRect(&run, 88, 110, 117);
        window.fillRect(&rdm_b, 255, 255, 255);
        window.fillRect(&rdm, 88, 110, 117);
        window.fillRect(&p1_b, 220, 50, 47);
        window.fillRect(&p1, 88, 110, 117);
        window.fillRect(&p2_b, 220, 50, 47);
        window.fillRect(&p2, 88, 110, 117);
        window.fillRect(&e1_b, 220, 50, 47);
        window.fillRect(&e1, 88, 110, 117);
        window.fillRect(&e2_b, 220, 50, 47);
        window.fillRect(&e2, 88, 110, 117);
        window.fillRect(&a1_b, 255, 255, 255);
        window.fillRect(&a1, 88, 110, 117);
        window.fillRect(&rs1_b, 255, 255, 255);
        window.fillRect(&rs1, 88, 110, 117);
        _k1.setTex("-", _k1_color, window.getRender());
        _k1.blitText(window.getRender(), &_k1_rect);
        _k2.setTex("+", _k1_color, window.getRender());
        _k2.blitText(window.getRender(), &_k2_rect);
        _run.setTex("RUN", _k1_color, window.getRender());
        _run.blitText(window.getRender(), &_run_rect);
        _random.setTex("RANDOM", _k1_color, window.getRender());
        _random.blitText(window.getRender(), &_random_rect);
        _points.setTex("NUMBER OF POINTS", _k1_color, window.getRender());
        _points.blitText(window.getRender(), &_points_rect);
        _error.setTex("ERROR", _k1_color, window.getRender());
        _error.blitText(window.getRender(), &_error_rect);
        _algorithm.setTex("BACK TO MENU", _k1_color, window.getRender());
        _algorithm.blitText(window.getRender(), &_algorithm_rect);
        _reset.setTex("RESET", _k1_color, window.getRender());
        _reset.blitText(window.getRender(), &_reset_rect);
        SDL_GetMouseState(&mouse_x, &mouse_y);
        //cout << mouse_x << " " << mouse_y << endl;
        if ((11 < mouse_y && mouse_y < 11 + 598) && (11 < mouse_x && mouse_x < 11 + 1178)) {
            SDL_Rect mouse_pos = {mouse_x, mouse_y, 10, 10};
            SDL_Rect text_poss = {mouse_x + 20, mouse_y, 100, 20};
            window.fillRect(&mouse_pos, 42, 161, 152);
            texPos.setTex("[" + to_string(mouse_x - 11) + ":" + to_string(mouse_y - 11) + "]", texPos_color, window.getRender());
            texPos.blitText(window.getRender(), &text_poss);
 
        }
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                cout << "Press Exit" << endl; 
                window.isRunning = false;
                window.kmeansisRunning = false;
                window.clear();
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if ((11 < mouse_y && mouse_y < 11 + 598) && (11 < mouse_x && mouse_x < 11 + 1178)) {
                    labels.clear();
                    vector<double> tmp;
                    int x = mouse_x - 11;
                    int y = mouse_y - 11;
                    tmp.push_back(x);
                    tmp.push_back(y);
                    points.push_back(tmp);
                    tmp.clear();
                }
                // Click on K- button
                if ((640 < mouse_y && mouse_y < 640 + 30) && (50 < mouse_x && mouse_x < 50 + 30)) {
                    cerr << "K- exc" << endl;
                    if (K > 0) K = K - 1;
                }
                // Click on K+ button
                if ((640 < mouse_y && mouse_y < 640 + 30) && (180 < mouse_x && mouse_x < 180 + 30)) {
                    cerr << "K+ exc" << endl;
                    if (K < 8) K = K + 1;
                }

                //Click random
                if ((640 < mouse_y && mouse_y < 640 + 30) && (390 < mouse_x && mouse_x < 390 + 110)) {
                //     clusters.clear();
                    clusters.clear();
                //     labels.clear();
                    labels.clear();
                    for (int i = 0; i < K; i++) {
                        int r1 = 10 + rand() % (1178 - 10 + 1 - 10);
                        int r2 = 10 + rand() % (598 - 10 + 1 - 10);
                        vector<double> rand;
                        rand.push_back(r1);
                        rand.push_back(r2);
                        clusters.push_back(rand);
                        rand.clear();
                    }
                    cerr << "Random exc" << endl;
               
                }
                // run
                if ((640 < mouse_y && mouse_y < 640 + 30) && (180 + 30 + 50 < mouse_x && mouse_x < 180 + 30 + 50 + 80) && clusters.size() != 0) {
                    // change points color
                    labels.clear();
                    for (int i = 0; i < points.size(); i++) {
                        vector<double> distance_to_cl;
                        for (int j = 0; j < clusters.size(); j++) {
                            double tmp1 = dis(points[i], clusters[j]);
                            distance_to_cl.push_back(tmp1);
                        }
                        double min_dis = *min_element(distance_to_cl.begin(), distance_to_cl.end());
                        labels.push_back(getIndex(distance_to_cl, min_dis));
                    }
                    // change clusters pos
                    for (int i = 0; i < clusters.size(); i++) {
                        double sum_x = 0;
                        double sum_y = 0;
                        double count = 0;
                        for (int j = 0; j < points.size(); j++) {
                            if (labels[j] == i) {
                                sum_x = sum_x + points[j][0];
                                sum_y = sum_y + points[j][1];
                                count = count + 1;
                                
                            }
                        }
                        if (count != 0) {
                            clusters[i][0] = sum_x/count;
                            clusters[i][1] = sum_y/count;
                            
                        }
                    }
                    cerr << "run exc" << endl;
                }
                // RESET
                if ((640 < mouse_y && mouse_y < 640 + 30) && (1070 < mouse_x && mouse_x < 1070 + 80)) {
                    points.clear();
                    error= 0; 
                    clusters.clear();
                    labels.clear();
                    K = 0;
                    cerr << "reset exc" << endl;
                }
                if ((640 < mouse_y && mouse_y < 640 + 30) && (870 < mouse_x && mouse_x < 870 + 150)) {
                    window.menuisRunning = true;
                    window.kmeansisRunning = false;
                    window.imgcompressisRunning = false;
                    cerr << "return menu" << endl;
                }
            }
        }
            // draw points_null
            for (int i = 0; i < points.size(); i++) {
                SDL_Rect back_points = {int(points[i][0]), int(points[i][1]), 10, 10};
                window.fillRect(&back_points, 255, 255, 255);
                //window.display();
                if (labels.size() == 0) {
                    SDL_Rect points_null = {int(points[i][0] + 1), int(points[i][1] + 1), 8, 8};
                    window.fillRect(&points_null, 0, 0, 0);
                } else {
                    SDL_Rect points_null = {int(points[i][0] + 1), int(points[i][1] + 1), 8, 8};
                    window.fillRect(&points_null, random_color[int(labels[i])].r, random_color[int(labels[i])].g, random_color[int(labels[i])].b);
                }
            }
            // draw random points
            for (int i = 0; i < clusters.size(); i++) {
                SDL_Rect random_points = {int(clusters[i][0]), int(clusters[i][1]), 14, 14};
                window.fillRect(&random_points, 255, 255, 255);
                SDL_Rect random_points_1 = {int(clusters[i][0]) + 3, int(clusters[i][1]) + 3, 8, 8};
                window.fillRect(&random_points_1, random_color[i].r, random_color[i].g, random_color[i].b);
            }

            //error
            error = 0;
            if (labels.size() != 0 && clusters.size() != 0) {
                for (int i = 0; i < points.size(); i++) {
                    error = error + int(dis(points[i], clusters[labels[i]]));
                } 
            }
            if (error > 0) {
                ERROR.setTex(to_string(error), er, window.getRender());
                ERROR.blitText(window.getRender(), &error_rect);
            }
            SDL_Rect demo = {752, 623, 0, 0};
            

            ERROR.setTex(to_string(points.size()), er, window.getRender());
            ERROR.blitText(window.getRender(), &demo);
            
            SDL_Rect K_value = {120, 640, 0, 0};
            ERROR.setTex(to_string(K), er, window.getRender());
            ERROR.blitText(window.getRender(), &K_value);

            window.display();
            window.clear();
        
    } // end while visualization
    
}
    TTF_Quit();
    SDL_StopTextInput();
    if (count > 3) window.isRunning = false;
    window.cleanUp();
    return 0;
}
