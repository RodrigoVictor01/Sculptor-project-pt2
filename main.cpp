#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "./include/Sculptor.hpp"
#include "./include/FiguraGeometrica.hpp"
#include "./include/PutVoxel.hpp"
#include "./include/CutVoxel.hpp"
#include "./include/PutBox.hpp"
#include "./include/CutBox.hpp"
#include "./include/PutEllipsoid.hpp"
#include "./include/CutEllipsoid.hpp"
#include "./include/PutSphere.hpp"
#include "./include/CutSphere.hpp"


int main() {
    const char *inputFileName = "comandos.txt";
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada: " << inputFileName << std::endl;
        return 1;
    }
    std::cout << "Arquivo de entrada aberto com sucesso: " << inputFileName << std::endl;

    int nx = 0, ny = 0, nz = 0;


    // Ler as dimensões do arquivo
    std::string dimLine;
    if (std::getline(inputFile, dimLine)) {
        std::istringstream dimStream(dimLine);
        std::string dimCommand;
        dimStream >> dimCommand;
        if (dimCommand == "dim") {
            dimStream >> nx >> ny >> nz;
            std::cout << "Dimensões lidas: " << nx << " " << ny << " " << nz << std::endl;
            if (nx <= 0 || ny <= 0 || nz <= 0) {
                std::cerr << "Dimensões inválidas" << std::endl;
                return 1;
            }
        }
        else {
            std::cerr << "Comando de dimensão inválido" << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "Erro ao ler as dimensões do arquivo" << std::endl;
        return 1;
    }

    
    
    
    Sculptor sculptor(nx, ny, nz);
    
    std::cout << "Sculptor criado com dimensões: nx=" << nx << ", ny=" << ny << ", nz=" << nz << std::endl;

    std::vector<FiguraGeometrica *> figuras;
    std::string linha;

    // Verificação adicional
    if (inputFile.eof()) {
        std::cerr << "Fim do arquivo de entrada alcançado inesperadamente" << std::endl;
    }

    // Faz a leitura e processamento dos comandos do arquivo txt
    while (std::getline(inputFile, linha)) {
        std::cout << "Linha lida: " << linha << std::endl; // Verificação adicional
        std::stringstream ss(linha);
        std::string comando;
        ss >> comando;
        std::cout << "Comando lido: " << comando << std::endl;

        if (comando == "PutVoxel") {
            int x, y, z;
            float r, g, b, a;
            ss >> x >> y >> z >> r >> g >> b >> a;
            figuras.push_back(new PutVoxel(x, y, z, r, g, b, a));
        }
        else if (comando == "CutVoxel") {
            int x, y, z;
            ss >> x >> y >> z;
            figuras.push_back(new CutVoxel(x, y, z));
        }
        else if (comando == "PutBox") {
            int x0, x1, y0, y1, z0, z1;
            float r, g, b, a;
            ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
            figuras.push_back(new PutBox(x0, x1, y0, y1, z0, z1, r, g, b, a));
        }
        else if (comando == "CutBox") {
            int x0, x1, y0, y1, z0, z1;
            ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
            figuras.push_back(new CutBox(x0, x1, y0, y1, z0, z1));
        }
        else if (comando == "PutSphere") {
            int xcenter, ycenter, zcenter, radius;
            float r, g, b, a;
            ss >> xcenter >> ycenter >> zcenter >> radius >> r >> g >> b >> a;
            figuras.push_back(new PutSphere(xcenter, ycenter, zcenter, radius, r, g, b, a));
        }
        else if (comando == "CutSphere") {
            int xcenter, ycenter, zcenter, radius;
            ss >> xcenter >> ycenter >> zcenter >> radius;
            figuras.push_back(new CutSphere(xcenter, ycenter, zcenter, radius));
        }
        else if (comando == "PutEllipsoid") {
            int xcenter, ycenter, zcenter, rx, ry, rz;
            float r, g, b, a;
            ss >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz >> r >> g >> b >> a;
            figuras.push_back(new PutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz, r, g, b, a));
        }
        else if (comando == "CutEllipsoid") {
            int xcenter, ycenter, zcenter, rx, ry, rz;
            ss >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz;
            figuras.push_back(new CutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz));
        }
    }

    inputFile.close();

    
    for (FiguraGeometrica *figura : figuras) {
        figura->draw(sculptor);
        delete figura;
    }

    
    std::cout << "Chamando writeOFF" << std::endl;
    sculptor.writeOFF("arquivo.off");

    return 0;
}
