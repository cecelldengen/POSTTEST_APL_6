#include <iostream>
#include <string>
using namespace std;

struct Drakor {
    string judul;
};

struct User {
    string id;
    string pass;
};

struct GudangDrakor {
    Drakor drakor[1000];
    int jumlah_data;
};

User* users = nullptr;

void bubbleSortAscending(string arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selectionSortDescending(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_idx]) {
                max_idx = j;
            }
        }
        swap(arr[i], arr[max_idx]);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int binarySearchAscending(const string arr[], int low, int high, const string key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int linearSearch(const string arr[], int n, const string key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

void login(User* user) {
    cout << "Masukkan id dan password" << endl;
    string id_login;
    string pass_login;
    int attempt = 3;
    while (attempt > 0) {
        cout << "ID: ";
        getline(cin, id_login);
        cout << "Password: ";
        getline(cin, pass_login);
        bool authenticated = false;
        if (user->id == id_login && user->pass == pass_login) {
            authenticated = true;
        }
        if (authenticated) {
            cout << "Berhasil login!" << endl;
            return;
        } else {
            cout << "ID atau password salah!" << endl;
            attempt--;
            cout << "Tersisa: " << attempt << " percobaan" << endl << endl;
            if (attempt == 0) {
                cout << "Anda di kick!" << endl;
                delete[] users;
                exit(0);
            }
        }
    }
}

void addDrakor(GudangDrakor &gudang) {
    cout << "Tambah drakor" << endl;
    string ulang;
    do {
        cout << "Masukkan judul drakor: ";
        getline(cin, gudang.drakor[gudang.jumlah_data].judul);
        gudang.jumlah_data++;
        cout << "Apakah ingin menambah lagi? (y/n): ";
        cin >> ulang;
        cin.ignore();
    } while (ulang == "y");
}

void listDrakor(const GudangDrakor &gudang) {
    cout << "List drakor" << endl;
    for (int i = 0; i < gudang.jumlah_data; i++) {
        cout << "Drakor ke-" << i + 1 << ": " << gudang.drakor[i].judul << endl;
    }
}

void displayUser(const User* user) {
    cout << "Informasi Pengguna:" << endl;
    cout << "ID: " << user->id << endl;
    cout << "Password: " << user->pass << endl;
}

void updateDrakor(GudangDrakor &gudang) {
    int ubah;
    cout << "Ubah data drakor" << endl;
    for (int i = 0; i < gudang.jumlah_data; i++) {
        cout << "Drakor ke-" << i + 1 << ": " << gudang.drakor[i].judul << endl;
    }
    cout << "Masukkan nomor yang ingin diubah: ";
    cin >> ubah;
    cin.ignore();
    cout << "Masukkan judul drakor baru: ";
    getline(cin, gudang.drakor[ubah - 1].judul);
}

void deleteDrakor(GudangDrakor &gudang) {
    int hapus;
    string ulang;
    do {
        cout << "Hapus drakor: ";
        cin >> hapus;
        cin.ignore();
        if (hapus >= 1 && hapus <= gudang.jumlah_data) {
            for (int i = hapus - 1; i < gudang.jumlah_data - 1; i++) {
                gudang.drakor[i] = gudang.drakor[i + 1];
            }
            gudang.jumlah_data--;
        } else {
            cout << "Nomor tidak valid" << endl;
        }
        cout << "Ingin menghapus lagi? (y/n): ";
        cin >> ulang;
    } while (ulang == "y");
}

void binarySearchMenu(const GudangDrakor &gudang); // Deklarasi fungsi binarySearchMenu
void linearSearchMenu(const GudangDrakor &gudang); // Deklarasi fungsi linearSearchMenu

void searchMenu(const GudangDrakor &gudang) {
    int pilih;
    cout << "Menu Pencarian" << endl;
    cout << "1. Binary Search (Ascending)" << endl;
    cout << "2. Linear Search" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilih;
    cin.ignore();
    switch (pilih) {
        case 1:
            binarySearchMenu(gudang);
            break;
        case 2:
            linearSearchMenu(gudang); // Panggilan fungsi sebelumnya yang belum dideklarasikan
            break;
        default:
            cout << "Inputan tidak valid" << endl;
    }
}

void binarySearchMenu(const GudangDrakor &gudang) {
    string cari;
    cout << "Masukkan judul drakor yang ingin dicari: ";
    getline(cin, cari);
    string* judulArr = new string[gudang.jumlah_data];
    for (int i = 0; i < gudang.jumlah_data; i++) {
        judulArr[i] = gudang.drakor[i].judul;
    }
    bubbleSortAscending(judulArr, gudang.jumlah_data);
    int hasil = binarySearchAscending(judulArr, 0, gudang.jumlah_data - 1, cari);
    if (hasil != -1) {
        cout << "Judul ditemukan pada indeks: " << hasil << endl;
    } else {
        cout << "Judul tidak ditemukan" << endl;
    }
    delete[] judulArr;
}

void linearSearchMenu(const GudangDrakor &gudang) {
    string cari;
    cout << "Masukkan judul drakor yang ingin dicari: ";
    getline(cin, cari);
    bool found = false;
    for (int i = 0; i < gudang.jumlah_data; i++) {
        if (gudang.drakor[i].judul == cari) {
            found = true;
            cout << "Judul ditemukan pada indeks: " << i << endl;
            break;
        }
    }
    if (!found) {
        cout << "Judul tidak ditemukan" << endl;
    }
}

void menu(GudangDrakor &gudang) {
    int pilih;
    string judul = "Welcome to Gudang Drakor";
    cout << judul << endl;
    cout << "List menu" << endl;
    cout << "1. Tambah drakor" << endl;
    cout << "2. List drakor" << endl;
    cout << "3. Ubah drakor" << endl;
    cout << "4. Hapus drakor" << endl;
    cout << "5. Tampilkan informasi pengguna" << endl;
    cout << "6. Pencarian" << endl;
    cout << "7. Exit" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilih;
    cin.ignore();
    switch (pilih) {
        case 1:
            addDrakor(gudang);
            break;
        case 2:
            listDrakor(gudang);
            break;
        case 3:
            updateDrakor(gudang);
            break;
        case 4:
            deleteDrakor(gudang);
            break;
        case 5:
            displayUser(users);
            break;
        case 6:
            searchMenu(gudang);
            break;
        case 7:
            cout << "Program selesai..." << endl;
            delete[] users;
            exit(0);
        default:
            cout << "Inputan tidak ada" << endl;
    }
    menu(gudang);
}

int main() {
    GudangDrakor gudang;
    gudang.jumlah_data = 0;
    users = new User[1];
    users[0] = {"cecel", "2309106003"};
    login(users);
    menu(gudang);
    return 0;
}