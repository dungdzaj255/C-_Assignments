#include <iostream>
#include <vector>
#include <fstream>

class Maze{
    public:
        Maze(const unsigned int rows, const unsigned int columns);
        char& at(const unsigned int row, const unsigned int column);
        int rows() const;
        int columns() const;
        void setCordinates(const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d);
        void setMove(std::string move);
        void player();
    private:
        std::vector< std::vector<char> > layout;
        int exitr;
        int exitc;
        int enterr;
        int enterc;
        std::string playerMove;
};

Maze::Maze(const unsigned int rows, const unsigned int columns){
    if ( (rows == 0) || (columns==0) ) { throw std::runtime_error("could not read height and width of the maze"); }
    layout.resize(rows);
    for (int r=0; r<rows; r++){
        layout.at(r).resize(columns);
    }
}

int Maze::rows() const { return layout.size(); }

int Maze::columns() const { return layout.at(0).size(); }

char& Maze::at(const unsigned int row, const unsigned int column){
    return layout.at(row).at(column);
}

void Maze::setCordinates(const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d){
    exitr = a;
    exitc = b;
    enterr = c;
    enterc = d;
}

void Maze::setMove(std::string move){
    playerMove = move;
    for (int i = 0; i < playerMove.length(); i++){
        if (playerMove.at(i) != 'l' && playerMove.at(i) != 'r' && playerMove.at(i) != 'u' && playerMove.at(i) != 'd') { throw std::runtime_error("invalid move"); } 
    }
}

void Maze::player() {
    if (layout.at(exitr).at(exitc) != '.') {throw std::runtime_error("exit outside maze or off the path");}
    if (layout.at(enterr).at(enterc) != '.') {throw std::runtime_error("player outside maze or off the path");}
    layout.at(enterr).at(enterc) = 'P';
    layout.at(exitr).at(exitc) = 'x';
    int Positionr = enterr;
    int Positionc = enterc;
    for (int r=0; r<layout.size(); r++){
        for (int c=0; c<layout.at(0).size(); c++){
            std::cout << layout.at(r).at(c);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < playerMove.length(); i++){
        if (playerMove.at(i) == 'l'){
            Positionc = Positionc - 1;
        }
        else if (playerMove.at(i) == 'r') {
            Positionc = Positionc + 1;
        }
        else if (playerMove.at(i) == 'u'){
            Positionr = Positionr - 1;
        }
        else if (playerMove.at(i) == 'd'){
            Positionr = Positionr + 1;
        }
        if (layout.at(Positionr).at(Positionc) == 'l') {throw std::runtime_error("player outside maze or off the path");}
    }
   
    if (layout.at(Positionr).at(Positionc) == 'x') {
        layout.at(Positionr).at(Positionc) = 'P';
        layout.at(enterr).at(enterc) = '.';
        for (int r=0; r<layout.size(); r++){
            for (int c=0; c<layout.at(0).size(); c++){
                std::cout << layout.at(r).at(c);
            }
            std::cout << std::endl;
        }   
        std::cout << "The player reached the exit!\n";
    }
    else {
        layout.at(Positionr).at(Positionc) = 'P';
        layout.at(enterr).at(enterc) = '.';
        for (int r=0; r<layout.size(); r++){
            for (int c=0; c<layout.at(0).size(); c++){
                std::cout << layout.at(r).at(c);
            }
            std::cout << std::endl;
        }    
        std::cout << "The player did not reach the exit.\n";
    }
}

int main(int argc, char* argv[]){
    try
    {
        std::ifstream inFile;
        if (argc != 2) { throw std::runtime_error("no input filename given"); }
        inFile.open(argv[1]);
        if (!inFile.is_open()) { 
            std::cout << "an error occurred: could not open input file " << argv[1];
            return 1;
        }
        int height, width;
        inFile >> height >> width;
        Maze m(height,width);
        for (int r=0; r<m.rows(); r++){
            for (int c=0; c<m.columns(); c++){
                inFile >> m.at(r,c);
                if (m.at(r,c) == 'l' || m.at(r,c) == '.') { 
                    continue;
                }
                else{
                    throw std::runtime_error("could not read maze layout"); 
                }
            }
        }


        int a, b, c, d;
        if ((inFile >> a >> b >> c >> d).fail()) { throw std::runtime_error("could not read coordinates"); }
        m.setCordinates(a,b,c,d);


        std::string move;
        inFile >> move;
        m.setMove(move);
        m.player();

    }

    catch(std::exception& e)
    {
        std::cerr << "an error occurred: " << e.what() << '\n';
    }

    return 0;
}
