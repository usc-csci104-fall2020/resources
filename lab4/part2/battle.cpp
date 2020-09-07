#include "battle.h"

#include "attackMove.h"
#include <cstdlib>
#include <unistd.h>

Battle::Battle(Pokemon* a, Pokemon* b) : playerA(a), playerB(b) {
    playerAturn = (bool)(std::rand() % 2);

    std::cout << "    ,                           .::." << std::endl;
    std::cout << "                              .;:**'            AMC" << std::endl;
    std::cout << "                              `                  0" << std::endl;
    std::cout << "  .:XHHHHk.              db.   .;;.     dH  MX   0" << std::endl;
    std::cout << "oMMMMMMMMMMM       ~MM  dMMP :MMMMMR   MMM  MR      ~MRMN" << std::endl;
    std::cout << "QMMMMMb  \"MMX       MMMMMMP !MX' :M~   MMM MMM  .oo. XMMM 'MMM" << std::endl;
    std::cout << "  `MMMM.  )M> :X!Hk. MMMM   XMM.o\"  .  MMMMMMM X?XMMM MMM>!MMP" << std::endl;
    std::cout << "   'MMMb.dM! XM M'?M MMMMMX.`MMMMMMMM~ MM MMM XM `\" MX MMXXMM" << std::endl;
    std::cout << "    ~MMMMM~ XMM. .XM XM`\"MMMb.~*?**~ .MMX M t MMbooMM XMMMMMP" << std::endl;
    std::cout << "     ?MMM>  YMMMMMM! MM   `?MMRb.    `\"\"\"   !L\"MMMMM XM IMMM" << std::endl;
    std::cout << "      MMMX   \"MMMM\"  MM       ~0:           !Mh.\"\"\" dMI IMMP" << std::endl;
    std::cout << "      'MMM.                                             IMX" << std::endl;
    std::cout << "       ~M!M                                             IMP" << std::endl << std::endl;
}

void Battle::run() {
    unsigned int microseconds = 500000;
    while (playerA->getHP() && playerB->getHP()) {
        usleep(microseconds);
        std::cout << playerA->getName() << ": " << playerA->getHP() << "HP" << std::endl;
        std::cout << playerB->getName() << ": " << playerB->getHP() << "HP" << std::endl;
        Pokemon *offense, *defense;
        if (playerAturn) {
            offense = playerA;
            defense = playerB;
        } else {
            offense = playerB;
            defense = playerA;
        }

        int chooseMove = std::rand() % 4;
        int dmg = defense->attackedBy(offense->attackPowerOf(chooseMove));

        std::cout << offense->getName() << " uses " << offense->getMove(chooseMove);
        std::cout << ". It did " << dmg << " damage!" << std::endl << std::endl;

        playerAturn = !playerAturn;
    }

    if (playerA->getHP()) {
        std::cout << playerA->getName() << " wins!" << std::endl;
    } else {
        std::cout << playerB->getName() << " wins!" << std::endl;
    }
}