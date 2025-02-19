# Encriptador y Desencriptador de Archivos en C++
## Descripción
Este programa en C++ para Linux permite encriptar y desencriptar archivos utilizando un algoritmo de cifrado XOR con clave fija. Se implementa utilizando llamadas al sistema (open(), read(), write(), close()) y se ejecuta desde la línea de comandos con diferentes opciones.

## Características
- Uso de llamadas al sistema.
- Detección automática de archivos texto o binarios.
- Compatible con Linux y ejecutable desde cualquier directorio.

## Instalación y Uso
### 1. Compilar el programa
Ejecuta el siguiente comando en la terminal para compilar el programa:
```g++ -o xor_encryptor xor_encryptor.cpp```

### 2. Opciones de ejecución
El programa acepta las siguientes opciones:
```./xor_encryptor [OPCION] [ARCHIVO]```

-h o --help	Muestra la ayuda del programa.
-v o --version	Muestra la versión del programa.
-e [archivo] o --encrypt [archivo]	Encripta el archivo especificado.
-d [archivo] o --decrypt [archivo]	Desencripta el archivo especificado.

## Ejemplo de uso
Para encriptar un archivo de texto llamado prueba.txt
```./xor -e prueba.txt```

El archivo encriptado se generará como prueba.txt.enc

Para desencriptarlo:
```./xor -d prueba.txt.enc```

El archivo desencriptado se guardará como prueba.txt.enc.dec

## Explicación del Algoritmo
### 1. Tipo de archivo a procesar (Texto o Binario)
El programa detecta automáticamente si un archivo es texto o binario. Para ello, lee los primeros bytes del archivo y busca caracteres nulos (\0):
- Si encuentra caracteres nulos, lo considera binario.
- Si no los encuentra, lo trata como texto.

### 2. Algoritmo de Encriptación
Se usa un cifrado XOR con clave fija (0xAA). El proceso es el siguiente:

Leer el archivo de entrada en bloques de 1024 bytes.
1. Aplicar la operación XOR a cada byte con la clave (buffer[i] ^= 0xAA).
2. Escribir los datos transformados en el archivo de salida.
3. El mismo algoritmo se usa para desencriptar, ya que aplicar XOR dos veces con la misma clave recupera el mensaje original.

## 4. Instalar el Programa en el Sistema
Para ejecutar el programa desde cualquier ubicación, muévelo a /usr/local/bin/:

```sudo mv proyecto_1_os /usr/local/bin/```

Asegura que tenga permisos de ejecución:
```sudo chmod +x /usr/local/bin/proyecto_1_os```

## 5. Ejecutar el Programa desde Cualquier Lugar
Ahora puedes ejecutarlo desde cualquier directorio en la terminal:
```xor_encryptor -e prueba.txt```

Si el comando no se reconoce, recarga el PATH:
```source ~/.bashrc```

