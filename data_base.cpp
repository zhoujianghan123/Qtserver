#include "data_base.h"

data_base::mysql::mysql() {

    qDebug() << QSqlDatabase::drivers();

}
