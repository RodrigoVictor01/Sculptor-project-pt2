
#include "../include/Sculptor.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
      
Sculptor::Sculptor(int nx, int ny, int nz) {
  this->nx = nx;
  this->ny = ny;
  this->nz = nz;
  std::cout << "Construtor de Sculptor chamado com dimensões: nx=" << nx << ", ny=" << ny << ", nz=" << nz << std::endl;


v = new Voxel **[nx];
v[0] = new Voxel *[nx * ny];
v[0][0] = new Voxel[nx * ny * nz];

// Cria as linhas da matriz de ponteiros.  
for (int i = 1; i < nx; i++) {
  v[i] = v[i - 1] + ny;
}

// Cria as colunas da matriz de ponteiros.
for (int j = 1; j < nx * ny; j++) {
  v[0][j] = v[0][j - 1] + nz;
}



 for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        v[i][j][k].show = false;
        v[i][j][k].r = 0.0;
        v[i][j][k].g = 0.0;
        v[i][j][k].b = 0.0;
        v[i][j][k].a = 0.0;
        // std::cout << "v[" << i << "][" << j << "][" << k << "] =  aaaa"
        //           << std::endl;
      }
    }
  }
}


Sculptor::~Sculptor() {

  delete[] v[0][0];
  delete[] v[0];
  delete[] v;
  std::cout << "Destrutor eficiente invocado" << std::endl;
}

void Sculptor::setColor(float r, float g, float b, float a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}
void Sculptor::putVoxel(int x, int y, int z) {
  if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
    v[x][y][z].show = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
  }
}

void Sculptor::cutVoxel(int x, int y, int z) {
  if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
    v[x][y][z].show = false;
  }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int x = x0; x <= x1; ++x) {
    for (int y = y0; y <= y1; ++y) {
      for (int z = z0; z <= z1; ++z) {
        putVoxel(x, y, z);
      }
    }
  }
}
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int x = x0; x <= x1; ++x) {
    for (int y = y0; y <= y1; ++y) {
      for (int z = z0; z <= z1; ++z) {
        cutVoxel(x, y, z);
      }
    }
  }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int x = xcenter - radius; x <= xcenter + radius; ++x) {
    for (int y = ycenter - radius; y <= ycenter + radius; ++y) {
      for (int z = zcenter - radius; z <= zcenter + radius; ++z) {
        if (sqrt((x - xcenter) * (x - xcenter) + (y - ycenter) * (y - ycenter) + (z - zcenter) * (z - zcenter)) <= radius) {
          putVoxel(x, y, z);
        }
      }
    }
  }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int x = xcenter - radius; x <= xcenter + radius; ++x) {
    for (int y = ycenter - radius; y <= ycenter + radius; ++y) {
      for (int z = zcenter - radius; z <= zcenter + radius; ++z) {
        if (sqrt((x - xcenter) * (x - xcenter) + (y - ycenter) * (y - ycenter) + (z - zcenter) * (z - zcenter)) <= radius) {
          cutVoxel(x, y, z);
        }
      }
    }
  }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
  for (int x = xcenter - rx; x <= xcenter + rx; ++x) {
    for (int y = ycenter - ry; y <= ycenter + ry; ++y) {
      for (int z = zcenter - rz; z <= zcenter + rz; ++z) {
        if ((pow(x - xcenter, 2) / pow(rx, 2) +
             pow(y - ycenter, 2) / pow(ry, 2) +
             pow(z - zcenter, 2) / pow(rz, 2)) <= 1.0) {
          putVoxel(x, y, z);
        }
      }
    }
  }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
  for (int x = xcenter - rx; x <= xcenter + rx; ++x) {
    for (int y = ycenter - ry; y <= ycenter + ry; ++y) {
      for (int z = zcenter - rz; z <= zcenter + rz; ++z) {
        if ((pow(x - xcenter, 2) / pow(rx, 2) +
             pow(y - ycenter, 2) / pow(ry, 2) +
             pow(z - zcenter, 2) / pow(rz, 2)) <= 1.0) {
          cutVoxel(x, y, z);
        }
      }
    }
  }
}

void Sculptor::writeOFF(const char *filename) {

  std::ofstream outfile(filename);

  if (!outfile.is_open()){
    std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
    return;
  }

 std::cout << "Escrevendo OFF com dimensões: nx=" << nx << ", ny=" << ny << ", nz=" << nz << std::endl;

  int numVertices = 0;
  int numFaces = 0;

  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if (v[i][j][k].show) {
          numVertices += 8;
          numFaces += 6;
        }
      }
    }
  }

  outfile << "OFF" << std::endl;
  outfile << numVertices << " " << numFaces << " 0" << std::endl;
  
  int vertexIndex = 0;

  
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if (v[i][j][k].show){

          outfile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          outfile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          outfile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          outfile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          outfile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          outfile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          outfile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          outfile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;

        }
      }
    }
  }

// int baseIndex = vertexIndex * 8;
for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
        for (int k = 0; k < nz; k++) {
            if (v[i][j][k].show) {
              
                int baseIndex = vertexIndex * 8;
                outfile << "4 " << baseIndex + 0 << " " << baseIndex + 3 << " "
                        << baseIndex + 2 << " " << baseIndex + 1 << " "
                        << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                        << " " << v[i][j][k].a << "\n";
                outfile << "4 " << baseIndex + 4 << " " << baseIndex + 5 << " "
                        << baseIndex + 6 << " " << baseIndex + 7 << " "
                        << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                        << " " << v[i][j][k].a << "\n";
                outfile << "4 " << baseIndex + 0 << " " << baseIndex + 1 << " "
                        << baseIndex + 5 << " " << baseIndex + 4 << " "
                        << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                        << " " << v[i][j][k].a << "\n";
                outfile << "4 " << baseIndex + 0 << " " << baseIndex + 4 << " "
                        << baseIndex + 7 << " " << baseIndex + 3 << " "
                        << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                        << " " << v[i][j][k].a << "\n";
                outfile << "4 " << baseIndex + 3 << " " << baseIndex + 7 << " "
                        << baseIndex + 6 << " " << baseIndex + 2 << " "
                        << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                        << " " << v[i][j][k].a << "\n";
                outfile << "4 " << baseIndex + 1 << " " << baseIndex + 2 << " "
                        << baseIndex + 6 << " " << baseIndex + 5 << " "
                        << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
                        << " " << v[i][j][k].a << "\n";
                vertexIndex++;
            }
        }
    }
}

  outfile.close();

 std ::cout << "Arquivo " << filename << " criado" << std::endl;

}