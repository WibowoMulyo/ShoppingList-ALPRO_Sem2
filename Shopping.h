#ifndef SHOPPING_H_INCLUDED
#define SHOPPING_H_INCLUDED
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const string FILENAME = "shopping.txt";

class Shopping
{
public:
    //KAMUS GLOBAL
    int opsi;
    string namabrg;
    int qty;
    int hargabrg;
    int totalhrg;
    int no;

    string choice;

    // Prosedur untuk menampilkan menu utama
    void MenuAwal()
    {
        cout << "=========================:WELCOME TO PROGRAM SHOPPING LIST:========================" << endl;
        cout << "Pilih salah satu opsi pada menu!" << endl;
        cout << "1. Input product" << endl;
        cout << "2. Display shopping list" << endl;
        cout << "3. Search product" << endl;
        cout << "4. Delete product" << endl;
        cout << "5. Edit product" << endl;
        cout << "6. Hitung subtotal harga product" << endl;
        cout << "7. Reset shopping list" << endl;
        cout << "8. Exit program" << endl;
        cout << "Opsi: ";
        cin >> opsi;
    }

    // Prosedur untuk menginput data product ke file shopping.txt
    void InputProduct()
    {
        cout << "Input nama product\t: ";
        cin.ignore();
        getline(cin, namabrg);
        cout << "Input quantity\t\t: ";
        cin >> qty;
        cout << "Input harga product\t: ";
        cin >> hargabrg;
        totalhrg = TotalHargaPerItem(qty, hargabrg);
        cout << "Total harga per item\t: " << totalhrg << endl;

        ofstream fout;
        fout.open(FILENAME, ios::app);

        fout << namabrg << " " << qty << " " << hargabrg << " " << totalhrg << " " << "\n";
        fout.close();

        cout << endl;
        cout << "Product berhasil ditambahkan.\n";
    }

    // Prosedur untuk menampilkan data yang ada pada file shopping.txt yang sudah diinput
    void ListProduct ()
    {
        ifstream fin;
        fin.open(FILENAME);

        cout << "+------+---------------------------+------------+----------------+----------------+\n";
        cout << "| No   | Nama Barang               | Quantity   | Harga          | Total Harga    |\n";
        cout << "+------+---------------------------+------------+----------------+----------------+\n";
        int no = 1;
        bool dataFound = false;
        while (fin >> namabrg >> qty >> hargabrg >> totalhrg)
        {
            cout << "| " << setw(4) << no << " | ";
            cout << setw(25) << namabrg << " | ";
            cout << setw(10) << qty << " | ";
            cout << "Rp" << setw(12) << hargabrg << " | ";
            cout << "Rp" << setw(12) << totalhrg << " | ";
            cout << endl;
            no = no + 1;
            dataFound = true;
        }
        if (!dataFound)
        {
            cout << "|                            Tidak ada produk                                     |\n";

        }
        cout << "+------+---------------------------+------------+----------------+----------------+\n";


        fin.close();

    }

    // Fungsi untuk mencari product berdasarkan nama barang di file shopping.txt
    void SearchProduct(string NamaProduct) {
        ifstream fin(FILENAME);
        if (fin.is_open())
        {
            bool found = false;
            while (fin >> namabrg >> qty >> hargabrg >> totalhrg)
            {
                if (namabrg == NamaProduct)
                {
                    found = true;
                    break;
                }
            }

            fin.close();

            if (found)
            {
                cout << "+---------------------------+------------+----------------+----------------+\n";
                cout << "| Nama Barang               | Quantity   | Harga          | Total Harga    |\n";
                cout << "+---------------------------+------------+----------------+----------------+\n";
                cout << "| " <<setw(25) << namabrg << " | ";
                cout << setw(10) << qty << " | ";
                cout << "Rp" << setw(12) << hargabrg << " | ";
                cout << "Rp" << setw(12) << totalhrg << " | ";
                cout << endl;
                cout << "+---------------------------+------------+----------------+----------------+\n\n";
            }
            else
            {
                cout << "Product not found.\n" << endl;
            }
        }
        else
        {
            cout << "File tidak dapat dibuka.\n" << endl;
        }
    }

    // Prosedur untuk menghapus product berdasarkan nama product
    void DeleteProduct(string NamaProduct)
    {
        ifstream fin;
        fin.open(FILENAME);

        bool found = false;

        ofstream fout;
        fout.open("temp.txt", ios::app);

        while (fin >> namabrg >> qty >> hargabrg >> totalhrg)
        {
            if (namabrg == NamaProduct)
            {
                found = true;
            }
            else
            {
                // menulis data dari file ke file sementara tanpa mengubahnya
                fout << namabrg << " " << qty << " " << hargabrg << " " << totalhrg << " " << "\n";
            }
        }

        fin.close();
        fout.close();

        remove(FILENAME.c_str());
        rename("temp.txt", FILENAME.c_str());

        if (found)
        {
            cout << "Product berhasil dihapus.\n";
        }
        else
        {
            cout << "Product tidak ditemukan.\n";
        }
    }

    // Prosedur untuk mengedit data product berdasarkan nama product
    void EditProduct(string NamaProduct)
    {
        ifstream fin;

        fin.open(FILENAME);

        bool found = false;

        ofstream fout;

        fout.open("temp.txt", ios::app);

        while (fin >> namabrg >> qty >> hargabrg >> totalhrg)
        {
            if (namabrg == NamaProduct)
            {
                found = true;

                cout << endl;
                cout << "Input new quantity\t: ";
                cin >> qty;
                cout << "Input new harga product\t: ";
                cin >> hargabrg;
                totalhrg = TotalHargaPerItem(qty, hargabrg);
                cout << "Total harga per item\t: " << totalhrg << endl << endl;

                fout << namabrg << " " << qty << " " << hargabrg << " " << totalhrg << " " << "\n";
            }
            else
            {
                // menulis data dari file ke file sementara tanpa mengubahnya
                fout << namabrg << " " << qty << " " << hargabrg << " " << totalhrg << " " << "\n";
            }
        }

        fin.close();
        fout.close();

        remove(FILENAME.c_str()); //digunakanlah fungsi c_str() untuk mengonversi objek string FILENAME menjadi string C-style sehingga dapat digunakan oleh fungsi remove() dan rename().
        rename("temp.txt", FILENAME.c_str());

        if (found)
        {
            cout << "Edit product success.\n";
        }
        else
        {
            cout << "Product not found.\n";
        }
    }

    // Prosedur untuk menghapus semua data file shopping.txt
    void ResetFile()
    {
        ofstream fout(FILENAME, ios::out | ios::trunc); // Membuka file untuk penulisan (write) dengan mode truncate

        if (fout.is_open())
        {
            fout.close();
            cout << "Data shopping list telah di-reset." << endl;
        }
        else
        {
            cout << "Can't open file." << endl;
         }
    }

    // Prosedur untuk menampilkan tabel shopping list yang ditambahkan subtotal semua product
    void SubtotalHarga ()
    {
        ifstream fin;
        fin.open(FILENAME);

        double totalshop = 0;
        while (fin >> namabrg >> qty >> hargabrg >> totalhrg)
        {
            totalshop = totalshop + totalhrg;
        }

        fin.close();

        cout << "| Subtotal Harga: Rp" << setw(3) << totalshop << setw(57) << " |" << endl;
        cout << "+---------------------------------------------------------------------------------+\n";

    }

    // Fungsi untuk menghitung total harga barang
    int TotalHargaPerItem(int quantity, int harga)
    {
        return quantity * harga;
    }

    //Prosedur untuk menanyakan kembali ke menu utama atau tidak
    void BackToMenu ()
    {

        cout << "Kembali ke menu utama (y/n) :";
        cin >> choice;

    }


};

#endif // SHOPPING_H_INCLUDED
