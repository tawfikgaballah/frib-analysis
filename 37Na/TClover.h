#include <TObject.h>
#include <vector>

const int totcrystals = 52;  // Example value, adjust as necessary
const int nclovers = 16;     // Example value, adjust as necessary

class TClover : public TObject {
public:
    double time[totcrystals];
    unsigned int timecfd[totcrystals];
    int cfdfailbit[totcrystals];
    double timecal[totcrystals];
    double energy[totcrystals];
    double ecal[totcrystals];
    int mult;

    // Simple add-back (no crosstalk corrections)
    double timeab[nclovers];
    double timecalab[nclovers];
    int cfdfailbitab[nclovers];  // OR of all cfdfailbits
    double ecalab[nclovers];
    int posmult[nclovers];
    int multab;

    int hit;

    void Reset() {
        // Reset all the arrays and members here
        for (int i = 0; i < totcrystals; i++) {
            time[i] = 0;
            timecfd[i] = 0;
            cfdfailbit[i] = 0;
            timecal[i] = 0;
            energy[i] = 0;
            ecal[i] = 0;
        }
        for (int i = 0; i < nclovers; i++) {
            timeab[i] = 0;
            timecalab[i] = 0;
            cfdfailbitab[i] = 0;
            ecalab[i] = 0;
            posmult[i] = 0;
        }
        mult = 0;
        multab = 0;
        hit = 0;
    }

    ClassDef(TClover, 2);  // ROOT macro for versioning and I/O support
};
