
#include "DelphesMain.h"
#include "DelphesSTDHEPInputReader.h"

#include "podio/SIOWriter.h"

int main(int argc, char *argv[]) {
  DelphesSTDHEPInputReader inputReader = DelphesSTDHEPInputReader();

  if (getFileEnding(argv[3]) == ".root") {
    return doit<podio::ROOTWriter>(argc, argv, inputReader);
  } else {
    return doit<podio::SIOWriter>(argc, argv, inputReader);
  }
}
