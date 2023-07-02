// Author : Wibowo Mulyo
// NIM    : A11.2022.14787
// Kelp   : 4219

#include <iostream>
#include <iomanip>
#include <string>
#include "shopping.h"; // Inklusi header file shopping.h

using namespace std;

//KAMUS GLOBAL
Shopping shop; // Deklarasi objek Shopping

// PROGRAM UTAMA
int main()
{
    // KAMUS LOKAL
    int n;
    string Product;

    do {
        system("cls"); // Membersihkan tampilan konsol
        shop.MenuAwal(); // Menampilkan menu awal

        switch (shop.opsi)
        {
            case 1:
                system("cls");
                cout << "=============================:FORM INPUT PRODUCT BELANJA:==========================" << endl;
                shop.InputProduct(); // Memanggil fungsi FormInput untuk menginput data barang belanja

                break;
            case 2:
                system("cls");
                cout << "===================================:SHOPPING LIST:=================================" << endl;
                shop.ListProduct(); // Menampilkan daftar belanja

                break;
            case 3:
                system("cls");
                cout << "===================================:SEARCH PRODUCT:================================" << endl;
                cout << "Input nama product yang ingin dicari: ";
                cin.ignore();
                getline(cin, Product);
                shop.SearchProduct(Product); // Memannggil method searching by nama product

                break;
            case 4:
                system("cls");
                cout << "===================================:DELETE PRODUCT:================================" << endl;
                shop.ListProduct();
                cout << "Input nama product yang ingin dihapus: ";
                cin.ignore();
                getline(cin, Product);
                shop.DeleteProduct(Product); // Memanggil method delete product by nama product

                break;
            case 5:
                system("cls");
                cout << "====================================:EDIT PRODUCT:=================================" << endl;
                shop.ListProduct();
                cout << "Input nama product yang ingin diedit: ";
                cin.ignore();
                getline(cin, Product);
                shop.EditProduct(Product); // Memanggil method edit product by nama product

                break;
            case 6:
                system("cls");
                cout << "============================:HITUNG SUBTOTAL HARGA PRODUCT:========================" << endl;
                shop.ListProduct();
                shop.SubtotalHarga();

                break;
            case 7:
                system("cls");
                shop.ResetFile();

                break;
            case 8:
                system("cls");
                cout << "Program selesai, Terima Kasih telah Menggunakan Program Kami :)" << endl;
                exit(0);
            default:
                cout << "Opsi tidak tersedia!" << endl;
                break;
        }
        shop.BackToMenu(); // Menampilkan pesan dan meminta input untuk kembali ke menu

        if (shop.choice != "y")
        {
            break;
        }
    } while (shop.choice == "y");

    return 0;
}
