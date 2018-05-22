#ifndef PRECOMPILECONSTANTS_H
#define PRECOMPILECONSTANTS_H
#define ARM_DEBUG

#define DBName "ARMDB"
#define ConnectionError "Ошибка подключения к БД, проверьте введенные данные и подключение к сети."

// код 1
#define DBCreationError "Ошибка, не найден драйвер для подключения к БД. Приложение будет закрыто."

// данные по умолчанию (администратора)
#define DefHost "localhost"
#define DefPort 5432
#define DefDBName "armp"
#define DefUserName "postgres"
#define DefPassword "PascalHate1"
#define DefIpHost "95.165.131.209"

// константы ДБ атрибутов

// таблица entrants и представление entrants_v

#define DefF_RegNum      "reg_num"
#define DefF_RegDate     "reg_date"
#define DefF_SecName     "sec_name"
#define DefF_Name        "name"
#define DefF_MidName     "mid_name"
#define DefF_BirthDate   "birth_date"
#define DefF_CitShip     "citizenship"
#define DefF_RegAdr      "reg_adr"
#define DefF_LivAdr      "live_adr"
#define DefF_PhonNum     "phone_number"
#define DefF_Email       "email"
#define DefF_EndEdYear   "end_educ_year"
#define DefF_AvgScr      "avg_score"
#define DefF_BenId       "benefit_id"
#define DefF_IsDorm      "is_dormitory_need"
#define DefF_IsRules     "is_rules_agreed"
#define DefF_IsDate      "is_date_agreed"
#define DefF_IsSPO       "is_first_spo"
#define DefF_IsProc      "is_data_proc_agreed"
#define DefF_Note        "note"
#define DefF_IsEnlstd    "is_courses"
#define DefF_SetId       "set_id"
#define DefF_Gender      "gender"
#define DefF_EducLvl     "educ_lvl"

#define DefF_EntrantsBenFKPK  "id"
#define DefF_EntrantsBenFAtr  "benefit_name"
#define DefF_EntrantsFTbl     "benefits"

#endif // PRECOMPILECONSTANTS_H
