#include "DOPE/dope_types.h"
#include "DOPE/dope_sheet.h"
#include "DOPE/dope_data_sheet.h"

int main() {
    //dope_sheet_t* sheet = dope_new_sheet();
    dope_data_sheet_t* data = dope_new_data_sheet();

    //dope_input_sheet(sheet, stdin);
    //dope_print_sheet(sheet);

    dope_input_data_sheet(data, stdin);
    dope_print_data_sheet(data);

    //dope_free_sheet(sheet);
    dope_free_data_sheet(data);

    return 0;
}
