#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define VERSION "1.0"

void show_help() {
    std::cout << "Uso: ./xor_encryptor [OPCION]... [ARCHIVO]...\n"
              << "Opciones:\n"
              << "  -h, --help            Muestra opciones de uso\n"
              << "  -v, --version         Muestra la versión del programa\n"
              << "  -e, --encrypt ARCHIVO Encripta el archivo especificado\n"
              << "  -d, --decrypt ARCHIVO Desencripta el archivo especificado\n";
}

void show_version() {
    std::cout << "file_encryptor versión " << VERSION << "\n";
}

bool is_binary_file(const std::string& filename) {
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return false;
    }

    char buffer[1024];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    close(fd);

    if (bytes_read == -1) {
        perror("Error al leer el archivo");
        return false;
    }

    for (ssize_t i = 0; i < bytes_read; ++i) {
        if (buffer[i] == '\0') {
            return true;
        }
    }
    return false;
}

void xor_encrypt_decrypt(const std::string& input_file, const std::string& output_file, char key) {
    int input_fd = open(input_file.c_str(), O_RDONLY);
    if (input_fd == -1) {
        perror("Error al abrir el archivo de entrada");
        return;
    }

    int output_fd = open(output_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        perror("Error al abrir el archivo de salida");
        close(input_fd);
        return;
    }

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytes_read; ++i) {
            buffer[i] ^= key;
        }
        if (write(output_fd, buffer, bytes_read) != bytes_read) {
            perror("Error al escribir en el archivo de salida");
            close(input_fd);
            close(output_fd);
            return;
        }
    }

    close(input_fd);
    close(output_fd);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        show_help();
        return 1;
    }

    std::string option = argv[1];
    if (option == "-h" || option == "--help") {
        show_help();
    } else if (option == "-v" || option == "--version") {
        show_version();
    } else if (option == "-e" || option == "--encrypt") {
        if (argc < 3) {
            std::cerr << "Error: Se requiere un archivo para encriptar.\n";
            return 1;
        }
        std::string file = argv[2];
        bool is_binary = is_binary_file(file);
        xor_encrypt_decrypt(file, file + ".enc", 0xAA); // Clave de encriptación simple
        std::cout << "Archivo encriptado guardado como " << file + ".enc" << "\n";
    } else if (option == "-d" || option == "--decrypt") {
        if (argc < 3) {
            std::cerr << "Error: Se requiere un archivo para desencriptar.\n";
            return 1;
        }
        std::string file = argv[2];
        bool is_binary = is_binary_file(file);
        xor_encrypt_decrypt(file, file + ".dec", 0xAA); // Clave de desencriptación simple
        std::cout << "Archivo desencriptado guardado como " << file + ".dec" << "\n";
    } else {
        std::cerr << "Opción no válida.\n";
        show_help();
        return 1;
    }

    return 0;
}