// Copyright 2020 Molotkova Svetlana
#ifndef MODULES_TASK_2_MOLOTKOVA_S_DINNING_PHILOSOPHERS_PHILOSOPHERS_H_
#define MODULES_TASK_2_MOLOTKOVA_S_DINNING_PHILOSOPHERS_PHILOSOPHERS_H_

void diningPhilosofers(int myRank, int ProcSize);
void table(bool* dinner, bool* fork, int ProcSize, std::list<int> ph_queue);
void philosofers();
bool check_hunger(int ProcSize, bool* dinner, int& out_buffer);

#endif  // MODULES_TASK_2_MOLOTKOVA_S_DINNING_PHILOSOPHERS_PHILOSOPHERS_H_
