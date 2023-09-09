#include "../include/initialise.h"

int main()
{

    Initialisation* initManager = Initialisation::GetInstance();
    if (initManager == nullptr)
    {
        std::cout << "initialisation failed" << std::endl;
        return 0;
    }

    TriangleMesh* tm = TriangleMesh::GetInstance();
    if(tm == nullptr)
    {
        std::cout << "triangle mesh uninitialised" << std::endl;
        return 0;
    }

    FileManager* fm = FileManager::GetInstance();
    if(fm == nullptr)
    {
        std::cout << "file manager initialisation failed" << std::endl;
        return 0;
    }

    int n = 1000;
    int* c_i = new int[n];
    test(c_i, n);

    // test
    for (int i = 0; i < n; i++) {
        std::cout << "c[" << i << "] = " << c_i[i] << std::endl;
    }

    delete[] c_i;

    fm->readObjFile("C:/Users/gopik/OneDrive/Desktop/models/icoSphere.obj", tm);

    return 0;
}