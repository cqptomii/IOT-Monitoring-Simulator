//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SCHEDULER_HPP
#define TP_SCHEDULER_HPP


class Scheduler {
private:
public:
    /**
     * @brief Constructeur par default de la classe Scheduler
     */
    Scheduler();
    /**
     * @brief Constructeur de recopie de la classe Scheduler
     *
     * @param scheduler : Scheduleur à recopier
     */
    Scheduler(const Scheduler& scheduler);
    /**
     * @brief Destructeur de la classe Scheduler
     */
    ~Scheduler() = default;
    /**
     * @brief Opérateur de copie de la classe Scheduler
     *
     * @param scheduler : Scheduler à copier
     */
    Scheduler& operator=(const Scheduler& scheduler);
};


#endif //TP_SCHEDULER_HPP
