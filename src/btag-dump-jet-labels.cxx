#include "Jets.hh"
#include "JetLabels.hh"

#include <iostream>


int main(int /*argc*/, char** /*argv*/) {
  // OutJet<JetLabels> labels;
  // std::cout << labels << std::endl;

  TrkUnitLabels trk_labels;
  std::cout << str_from_out_unit(trk_labels) << std::endl;
  return 0;
}
