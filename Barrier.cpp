//
// Created by tomfr on 09/10/2024.
//

#include "Barrier.hpp"
/**
 * @brief Constructeur par défault de la classe Barrier
 */
Barrier::Barrier() : thread_amount(0), thread_waiting(0) {}
/**
 * @brief Constructeur surchargé de la classe Barrier
 * @param count : nombre de threads du programme
 */
Barrier::Barrier(unsigned int count) : thread_waiting(0), thread_amount(count) {}
/**
 * @brief méthode permettant de mettre en pause les threads jusqu'a ce que l'ensemble des threads aient fini leurs taches
 * l'utilisation d'un mutex et d'une variable de condition permet de bloquer les threads tant qu'une certaine condition n'est pas rempli
 */
void Barrier::wait() {
    std::unique_lock<std::mutex> lock(mtx);
    ++thread_waiting;

    if(thread_waiting == thread_amount){
        thread_waiting = 0;
        cv.notify_all();
    }else{
        // Attend jusqu'à que la condition thread_waiting == 0 soit rempli
        cv.wait(lock,[this]{ return thread_waiting == 0; });
    }
}