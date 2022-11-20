from random import randint
def write(filename,data):
  archivo = open(filename,"w")
  archivo.write(data)
  archivo.close()

OUTPUT = ""
FILENAME = "informe-nautico.txt"
K = 2 # Factor de dupliacion
M = 3 # Largo embarcación
N = M*2**K
OUTPUT += str(N) + "\n"
OUTPUT += str(M) + "\n"
matriz = [["0" for y in range(0,N)] for x in range(0,N)]
x = M*randint(0,N/M - 1)
y = randint(0,N - 1)
for i in range(0,M):
  matriz[y][x + i] = "1"
for i in range(0,N):
  matriz[i] = "[" + " ".join(matriz[i]) + "]"
matriz = ",".join(matriz)
OUTPUT += str(matriz) + "\n"
write(FILENAME,OUTPUT)
print(f"Respuesta esperada -> fila {y + 1} columna {x + 1}.")