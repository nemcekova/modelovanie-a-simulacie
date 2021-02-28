/**********************************************************************************
 * Predmet: IMS Modelovanie a simulácie FIT VUT 2019                              *
 * Project: Plasty -Vplyv výroby plastov na svetové zásoby ropy                   *
 * @brief: Hlavný súbor: plasty.cpp                                               *
 * @authors : René Bolf (xbolfr00@vutbr.cz) Barbora Nemčeková (xnemce06@vutbr.cz) *
 *********************************************************************************/

#include<stdio.h>
#include<stdlib.h> /* srand, rand*/
#include<math.h>
#include<iostream>
#include <err.h>
#include<ctype.h>
#include<string.h>
#include <time.h> /* time */


void print_usage()
{
  std::cout << "-r priemerny nárast v zásobách ropy v percentách za jeden rok. " << '\n';
  std::cout << "-p priemerny nárast v produkcií plastov v milionoch ton za jeden rok. " << '\n';
  std::cout << "Implicitné zadané hodnoty u plastov 7 milionov ton. " << '\n';
  std::cout << "Implicitná hodnota u ropy je 13 percent. " << '\n';
  std::cout << "Hodnoty sú vypočítané na základe priemeru za posledných 50 rokov. " << '\n';
  exit(2);
}

int main(int argc, char *argv[]) {
  int option;
  float prirast_ropy;
  unsigned long int prirast_plastov;
  unsigned long int plasty_produkcia = 381000000; //vyrobene plasty v roku 2015 v tonach
  unsigned long int ropa_za_den = 13250414; //pouzita ropa za den pre rok 2015 v tonach
  unsigned long int ropa_za_rok = ropa_za_den * 365; // pouzita ropa za rok 2015 v tonach
  unsigned long int zasoby_ropy = 226209509558; //zasoby ropy pre rok 2015 v tonach

  srand (time(NULL));
  if (argc > 1) {

      if(argc == 3){
          if((strcmp(argv[1],"-r") == 0)){
              prirast_ropy = atoi(argv[2]);
              prirast_plastov = 7000000;
          }

          else if((strcmp(argv[1],"-p") == 0)){
              prirast_plastov = atoi(argv[2]) * 1000000;
              prirast_ropy = 13;
          }

          else{
            std::cerr << "Error zle zadane argumenty " << '\n';
            return EXIT_FAILURE;
          }
      }
      else if(argc == 2){
        if((strcmp(argv[1],"-h") == 0)){
          print_usage();
        }
        else
          std::cerr << "Error zle zadane argumenty " << '\n';
          return EXIT_FAILURE;
      }

      else if(argc == 5){
          if(((strcmp(argv[1],"-r") == 0) && (strcmp(argv[3],"-p")) == 0)){
              prirast_ropy = atoi(argv[2]);
              prirast_plastov = atoi(argv[4]) * 1000000;
          }

          else if(((strcmp(argv[1],"-p")== 0) && (strcmp(argv[3],"-r")) == 0)){
              prirast_plastov = atoi(argv[2]) * 1000000;
              prirast_ropy = atoi(argv[4]);
          }
          else{
            std::cerr << "Error zle zadane argumenty " << '\n';
            return EXIT_FAILURE;
          }
      }

      else{
        std::cerr << "Error zle zadane argumenty " << '\n';
        return EXIT_FAILURE;
      }
  }
  else{
      prirast_ropy = 13; //priemerny prirastok zasob ropy za poslednych 50 rokov (vdaka najdenym novym loziskam)
      prirast_plastov = 7000000; //priemerny prirastok v produkcii plastov za poslednych 50 rokov
  }


  float percenta_ropy = (float)prirast_ropy / 100; // 13/100 = 0,13


  for(int x = 2016; x <= 2050; x++)
  {
    plasty_produkcia += prirast_plastov; //produkcia plastov za posledny rok + priemerny prirastok
    double prirastok = zasoby_ropy * percenta_ropy; //prirastok ropy vyratany z percent predchadzjuceho roku -- x = 0,13 * 226209509558 x = 2,94 *10 na 10
    zasoby_ropy += prirastok;  //k zasobam ropy sa prirata uz vyratany prirastok z predchadzajucich zasob -- 226209509558 + 2,94*10 na 10 = 2,556*10 na 11


    int prirastok_nahodny = rand()%168081 + 112054;// od 112054 do 280135

    ropa_za_rok += (prirastok_nahodny * 365); //prirastok v zasobach ropy za dany rok
    zasoby_ropy -= ropa_za_rok; // od zasob ropy sa odrataju ropa za rok

  }


  float pouzivana_ropa = (float)ropa_za_rok * 100.0 / (float)zasoby_ropy;
  std::cout << "V roku 2050 bude vyuzitych " << pouzivana_ropa << "% z celkovej zasoby ropy\n";

  // kolko percent ropy sa bude vyuzivat na vyrobu plastu
  long int ropa_na_plasty =  plasty_produkcia * 2 * 100 / ropa_za_rok;
  std::cout << "Ropa vyuzita na plasty v roku 2050: " << ropa_na_plasty <<"%\n";

  long int ropa_bez_bio =  plasty_produkcia * 0.64 * 2 * 100 / ropa_za_rok;
  std::cout << "Ropa vyuzita na plasty v roku 2050, keby sa vsetky obaly nahradili bioplastom : " << ropa_bez_bio << "%\n";

  unsigned long int co2_plasty = plasty_produkcia * 6000;
  int co2_plasty_giga = co2_plasty / (pow(10, 9));

  std::cout << "co2 z vyroby plastov v roku 2050: " << co2_plasty_giga << " gigaton za rok 2050\n";

  unsigned long int co2_bez_bio = plasty_produkcia * 6000 * 0.64;
  int co2_bez_bio_giga = co2_bez_bio / (pow(10,9));

  std::cout << "co2 z vyroby plastov bez bio plastov v roku 2050: " << co2_bez_bio_giga << " gigaton za rok 2050\n";


  return 0;
}
