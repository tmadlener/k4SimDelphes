
#include "DelphesMain.h"
#include "DelphesPythia8Reader.h"

#include "podio/SIOWriter.h"

int main(int argc, char *argv[]) {
  DelphesPythia8Reader inputReader = DelphesPythia8Reader();

  if (getFileEnding(argv[4]) == ".root") {
    return doit<podio::ROOTWriter>(argc, argv, inputReader);
  } else {
    return doit<podio::SIOWriter>(argc, argv, inputReader);
  }
}
