#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

int openFile(const filesystem::path& direktoriCur) {
    system("cls");

    cout << "Direktori saat ini: " << direktoriCur.filename() << endl << endl;

    for (const auto& entry : filesystem::directory_iterator(direktoriCur)) {
        if (entry.is_regular_file()) {
            cout << " - " << entry.path().filename() << endl;
        }
    }

    string namaFile;
    cout << "\nMasukkan nama file: ";
    getline(cin, namaFile);

    ifstream file(namaFile);
    if (!file) {
        cerr << "Error file tidak bisa dibuka" << endl;
        return 1;
    }
    system("cls");
    
    string line;
    while (getline (file, line)) {
        cout << line << endl;
    }
    file.close();
    return 0;
}

int main() {
    bool benar = false;
    while (!benar) {
        system("cls");

        filesystem::path direktoriCur = filesystem::current_path();
        cout << "Direktori saat ini: " << direktoriCur.filename() << endl << endl;
        cout << "Apakah folder sudah sesuai? (Ketik 'next' jika tidak sesuai atau 'null' jika sesuai)" << endl;
        cout << "Masukkan input: ";
        string sesuai;
        cin >> sesuai;
        cin.ignore();

        bool benar2 = false;
        if (sesuai == "next") {
            benar = true;
            while (!benar2) {
                system("cls");
                direktoriCur = filesystem::current_path();
                cout << "Direktori saat ini: " << direktoriCur.filename() << endl << endl;
                cout << "Berikut adalah kumpulan subfolder dalam direktori ini: " << endl;

                for (const auto& entry : filesystem::directory_iterator(direktoriCur)) {
                    if (entry.is_directory()) {
                        cout << " - " << entry.path().filename() << endl;
                    }
                }

                cout << "\nPerintah:" << endl;
                cout << "1. Ketik 'up' untuk berpindah direktori sebelumnya" << endl;
                cout << "2. Ketik 'nama subFolder' untuk masuk ke subfolder tersebut" << endl;
                cout << "3. Ketik 'ok' jika direktori sudah sesuai" << endl;
                cout << "4. Ketik 'show' untuk tampilkan file dalam direktori ini" << endl;
                cout << "\nMasukkan perintah atau nama subfolder: ";
                string input;
                getline(cin, input);

                if (input == "up") {
                    filesystem::path parentDir = direktoriCur.parent_path();

                    if (parentDir == direktoriCur) {
                        cout << "Anda sudah berada di-direktori ini" << endl;
                        return 1;
                    } else {
                        direktoriCur = parentDir;
                        filesystem::current_path(direktoriCur);
                    }

                    system("cls");
                } else if (input == "ok") {
                    benar2 = true;
                    cout << "test" << endl;
                    break;
                } else if (input == "show") {
                    system("cls");
                    cout << "Direktori saat ini : " << direktoriCur.filename() << endl;
                    cout << "\nBerikut adalah kumpulan file dalam direktori ini" << endl;

                    for (const auto& entry : filesystem::directory_iterator(direktoriCur)) {
                        if (entry.is_regular_file()) {
                            cout << " - " << entry.path().filename() << endl;
                        }
                    }

                    cout << "\nTekan enter untuk kembali" << endl;
                    cin.get();
                    
                } else {
                    filesystem::path subFolder = direktoriCur / input;

                    if (filesystem::exists(subFolder) && filesystem::is_directory(subFolder)) {
                        filesystem::current_path(subFolder);
                    } else {
                        cout << "subfolder tidak ditemukan." << endl;
                    }
                }
            }
        }
    }

    openFile(filesystem::current_path());
    cin.get();
}
