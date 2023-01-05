#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Estudio {
  char region[20];
  int estado; // 1:activo  2:controlado   3:contenido
  int terrenoquemado;
  int mes;
};

struct campo {
  int estado, terrenoquemado;
};

struct campo01 {
  int region, terrenoquemado;
};

// creacion del archivo
void creacionDeArchivo(FILE *arch, int regs) {
  struct Estudio estudio[14] = {
      {"CUYO", 1, 320, 1},      {"CUYO", 2, 30, 1},
      {"CUYO", 2, 150, 1},      {"CUYO", 3, 100, 2},
      {"CUYO", 3, 50, 2},       {"NORESTE", 1, 50, 2},
      {"NORESTE", 2, 100, 3},   {"NOROESTE", 2, 20, 3},
      {"NOROESTE", 3, 100, 4},  {"PAMPEANA", 1, 74, 3},
      {"PAMPEANA", 1, 30, 5},   {"PATAGONICA", 2, 8, 5},
      {"PATAGONICA", 3, 12, 6}, {"PATAGONICA", 3, 27, 6},
  };

  arch = fopen("incendios-forestales.dat", "w"); // Creación de archivo

  if (arch == NULL) {
    fprintf(stderr, "\nError al abrir el archivo\n");
    exit(1);
  }

  regs = fwrite(estudio, sizeof(estudio), 1,
                arch); // Devuelve 1 si estatodo bien si no devuelve 0

 /*  if (regs != 0)
    printf("Se han guardado correctamente los datos!\n");
  else
    printf("Error al guardar!\n"); */

  fclose(arch);
}

// fin creacion de archivo

int clasifRegion(char b[]) {
  if (strcmp(b, "NORESTE") == 0) {
    return 1;
  }
  if (strcmp(b, "NOROESTE") == 0) {
    return 2;
  }
  if (strcmp(b, "CUYO") == 0) {
    return 3;
  }
  if (strcmp(b, "PAMPEANA") == 0) {
    return 4;
  }
  if (strcmp(b, "PATAGONICA") == 0) {
    return 5;
  }
}

void ordenarVector(struct campo01 m[6]) {
  int j;
  struct campo01 aux1;
  bool cambios = true;
  while (1) {
    // Esto se usa para la proxima vuelta, dentro del ciclo
    cambios = false;
    for (j = 1; j < 5; ++j) {
      // Comparo par de posiciones dentro del array
      if (m[j].terrenoquemado > m[j + 1].terrenoquemado) {
        // Hago el intercambio
        aux1.terrenoquemado = m[j].terrenoquemado;
        aux1.region = m[j].region;
        m[j] = m[j + 1];
        m[j + 1].terrenoquemado = aux1.terrenoquemado;
        m[j + 1].region = aux1.region;
        // Cambio el valor de verdad
        cambios = true;
      }
    }

    if (!cambios) {
      break;
    }
  }
}

char *clasifregiont(int b) {
  switch (b) {
  case 1:
    return "noreste";
    break;
  case 2:
    return "noroeste";
    break;
  case 3:
    return "cuyo";
    break;
  case 4:
    return "pampeana";
    break;
  case 5:
    return "patagonica";
    break;
  }
}

char *clasifmesnt(int a) {
  switch (a) {
  case 1:
    return "mayo";
    break;
  case 2:
    return "junio";
    break;
  case 3:
    return "julio";
    break;
  case 4:
    return "agosto";
    break;
  case 5:
    return "septiembre";
    break;
  case 6:
    return "octubre";
    break;
  }
}

int main() {

  FILE *f;
  struct campo v[7][8];
  struct campo01 m[6];
  struct campo01 aux1;
  struct Estudio reg;
  int x, y, contactiv, contcontro, contconten, cantincend, a, b, c, d, e,
  region, regs, mes, mesmayor, regionmayor, aux, max;
  creacionDeArchivo(f, regs); // Se crea el archivo
  f = fopen("incendios-forestales.dat", "r");
  if (f == NULL) {
    printf("no se a podido abrir el fichero.\n");
    exit(1);
  }

  for (x = 1; x < 7; x++) {
    for (y = 1; y < 8; y++) {
      v[x][y].estado = 0;
      v[x][y].terrenoquemado = 0;
    }
  }

  contactiv,contconten,contcontro,aux = 0;

  fread(&reg, sizeof(struct Estudio), 1, f);
  while (!feof(f)) {
    region = clasifRegion(reg.region);
    mes = reg.mes;
    v[region][mes].estado = reg.estado;
    v[region][mes].terrenoquemado =
        v[region][mes].terrenoquemado + reg.terrenoquemado;
    fread(&reg, sizeof(struct Estudio), 1, f);
  }
  fclose(f);
  for (y = 1; y < 7; y++) {
    for (x = 1; x < 6; x++) {
      v[x][7].terrenoquemado += v[x][y].terrenoquemado;
      v[x][7].estado = 0;
      switch (v[x][y].estado) {
      case 1:
        contactiv++;
        break;
      case 2:
        contcontro++;
        break;
      case 3:
        contconten++;
        break;
      }
      v[6][y].terrenoquemado += v[x][y].terrenoquemado;
      v[6][y].estado = 0;
    }
  }

  for (y = 1; y < 8; y++) {
    if (v[6][y].terrenoquemado > aux) {
      aux = v[6][y].terrenoquemado;
      mesmayor = y;
    }
  }

  for (x = 1; x < 6; x++) {
    m[x].region = x;
    m[x].terrenoquemado = v[x][7].terrenoquemado;
  }

  ordenarVector(m);

  printf("-------------------------------------------------\n");
  printf("------------------------------------------------- \n");

  printf("Hectareas del noreste es: %d \n", v[1][7].terrenoquemado);
  printf("Hectareas del noroeste es: %d \n", v[2][7].terrenoquemado);
  printf("Hectareas del cuyo es: %d \n", v[3][7].terrenoquemado);
  printf("Hectareas del pampeana es: %d \n", v[4][7].terrenoquemado);
  printf("Hectareas del patagonica es: %d \n", v[5][7].terrenoquemado);

  printf("-------------------------------------------------\n");
  printf("------------------------------------------------- \n");

  printf("La cantidad de incendios activos son: %d \n", contactiv);
  printf("La cantidad de incendios controlados son: %d \n", contcontro);
  printf("La cantidad de incendios contenido son: %d \n", contconten);

  printf("-------------------------------------------------\n");
  printf("------------------------------------------------- \n");

  printf("La región que mas se quemo es %s \n", clasifregiont(m[5].region));
  printf("-------------------------------------------------\n");
  printf("El mes que mas incendios contenidos tuvo fue %s \n",
         clasifmesnt(mesmayor));

  printf("-------------------------------------------------\n");
  printf("------------------------------------------------- \n");

  printf("Las regiones mas propensas a incendios son:  \n | %s       | \n | %s "
         "   | \n | %s   |\n | %s   | \n | %s |",
         clasifregiont(m[5].region), clasifregiont(m[4].region),
         clasifregiont(m[3].region), clasifregiont(m[2].region),
         clasifregiont(m[1].region));

  return 0;
}