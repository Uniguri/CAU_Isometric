#include "player.h"
#include "platform.h"
#include "turret.h"

extern ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
extern int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], level;
extern Player player;
extern SceneID gameScene[MAX_LEVEL];
extern Bullet bullets[100];
extern Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET];
extern heart_struct heart;

const char* const PlayerIdleImages[DirectionOfPlayerFace::DIRECTION_OF_PLAYER_FACE_SIZE][NUMBER_OF_PLAYER_IDLE_IMAGE_FOR_EACH_DIR] =
{
    {
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00000.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00001.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00002.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00003.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00004.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00005.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00006.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00007.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00008.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00009.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00010.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00011.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00012.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00013.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00014.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_00015.png"
    },
    {
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10000.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10001.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10002.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10003.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10004.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10005.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10006.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10007.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10008.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10009.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10010.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10011.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10012.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10013.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10014.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_10015.png"
    },
    {
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20000.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20001.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20002.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20003.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20004.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20005.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20006.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20007.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20008.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20009.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20010.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20011.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20012.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20013.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20014.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_20015.png"
    },
    {
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30000.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30001.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30002.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30003.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30004.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30005.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30006.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30007.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30008.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30009.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30010.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30011.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30012.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30013.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30014.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_30015.png"
    },
    {
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40000.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40001.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40002.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40003.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40004.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40005.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40006.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40007.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40008.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40009.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40010.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40011.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40012.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40013.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40014.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_40015.png"
    },
    {
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50000.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50001.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50002.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50003.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50004.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50005.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50006.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50007.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50008.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50009.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50010.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50011.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50012.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50013.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50014.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_50015.png"
    },
    {
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60000.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60001.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60002.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60003.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60004.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60005.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60006.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60007.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60008.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60009.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60010.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60011.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60012.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60013.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60014.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_60015.png"
    },
    {
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70000.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70001.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70002.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70003.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70004.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70005.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70006.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70007.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70008.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70009.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70010.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70011.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70012.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70013.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70014.png",
        "img/players/isometric_Mini-Crusader/idle/crusader_idle_70015.png"
    }

};
const char* const PlayerMoveImages[DirectionOfPlayerFace::DIRECTION_OF_PLAYER_FACE_SIZE][NUMBER_OF_PLAYER_MOVE_IMAGE_FOR_EACH_DIR] =
{
    {"img/players/isometric_Mini-Crusader/run/crusader_run_00000.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00001.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00002.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00003.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00004.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00005.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00006.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00007.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00008.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00009.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00010.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00011.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00012.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00013.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00014.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00015.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_00016.png"},
    {"img/players/isometric_Mini-Crusader/run/crusader_run_10000.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10001.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10002.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10003.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10004.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10005.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10006.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10007.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10008.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10009.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10010.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10011.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10012.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10013.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10014.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10015.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_10016.png"},
    {"img/players/isometric_Mini-Crusader/run/crusader_run_20000.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20001.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20002.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20003.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20004.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20005.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20006.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20007.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20008.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20009.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20010.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20011.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20012.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20013.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20014.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20015.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_20016.png"},
    {"img/players/isometric_Mini-Crusader/run/crusader_run_30000.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30001.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30002.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30003.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30004.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30005.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30006.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30007.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30008.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30009.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30010.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30011.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30012.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30013.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30014.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30015.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_30016.png"},
    {"img/players/isometric_Mini-Crusader/run/crusader_run_40000.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40001.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40002.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40003.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40004.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40005.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40006.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40007.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40008.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40009.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40010.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40011.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40012.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40013.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40014.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40015.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_40016.png"},
    {"img/players/isometric_Mini-Crusader/run/crusader_run_50000.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50001.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50002.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50003.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50004.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50005.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50006.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50007.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50008.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50009.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50010.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50011.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50012.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50013.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50014.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50015.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_50016.png"},
    {"img/players/isometric_Mini-Crusader/run/crusader_run_60000.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60001.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60002.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60003.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60004.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60005.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60006.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60007.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60008.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60009.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60010.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60011.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60012.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60013.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60014.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60015.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_60016.png"},
    {"img/players/isometric_Mini-Crusader/run/crusader_run_70000.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70001.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70002.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70003.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70004.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70005.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70006.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70007.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70008.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70009.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70010.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70011.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70012.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70013.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70014.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70015.png",
    "img/players/isometric_Mini-Crusader/run/crusader_run_70016.png"}
};
const char* const PlayerAttackImages[DirectionOfPlayerFace::DIRECTION_OF_PLAYER_FACE_SIZE][NUMBER_OF_PLAYER_ATTACK_IMAGE_FOR_EACH_DIR] =
{
    {
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00000.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00001.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00002.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00003.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00004.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00005.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00006.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00007.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00008.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00009.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00010.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00011.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00012.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00013.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00014.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00015.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00016.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_00017.png"
    },
    {
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10000.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10001.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10002.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10003.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10004.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10005.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10006.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10007.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10008.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10009.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10010.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10011.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10012.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10013.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10014.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10015.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10016.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_10017.png"
    },
    {
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20000.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20001.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20002.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20003.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20004.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20005.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20006.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20007.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20008.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20009.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20010.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20011.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20012.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20013.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20014.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20015.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20016.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_20017.png"
    },
    {
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30000.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30001.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30002.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30003.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30004.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30005.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30006.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30007.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30008.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30009.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30010.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30011.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30012.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30013.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30014.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30015.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30016.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_30017.png"
    },
    {
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40000.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40001.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40002.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40003.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40004.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40005.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40006.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40007.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40008.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40009.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40010.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40011.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40012.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40013.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40014.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40015.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40016.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_40017.png"
    },
    {
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50000.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50001.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50002.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50003.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50004.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50005.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50006.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50007.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50008.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50009.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50010.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50011.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50012.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50013.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50014.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50015.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50016.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_50017.png"
    },
    {
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60000.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60001.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60002.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60003.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60004.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60005.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60006.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60007.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60008.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60009.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60010.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60011.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60012.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60013.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60014.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60015.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60016.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_60017.png"
    },
    {
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70000.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70001.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70002.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70003.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70004.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70005.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70006.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70007.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70008.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70009.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70010.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70011.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70012.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70013.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70014.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70015.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70016.png",
        "img/players/isometric_Mini-Crusader/attack/crusader_attack_70017.png"
    }
};
TimerID player_timer, moveAnimationTimer;
ObjectID animation1 = createObject("img/moveanimation.png"), animation2 = createObject("img/moveanimation.png");
SceneID moveScene = createScene("", "img/mainScene.png");
int animation1_Y = 360, animation2_Y = -360, cnt = 0;
bool isMovingLevel = false;

void heart_function() {
    heart.scene = gameScene[level];
    for (int i = 0; i < 5; i++) {
        heart.heart[i] = createObject("img/heart.png");
        locateObject(heart.heart[i], heart.scene, heart.heart_x[i], heart.heart_y);

    }
}
//
void ShowHeart() {
    for (int i = 0; i < heart.num_heart; i++) {
        heart.scene = gameScene[level];
        locateObject(heart.heart[i], heart.scene, heart.heart_x[i], heart.heart_y);
        showObject(heart.heart[i]);
    }
}

// knockback
void MinusHeart() {
    for (int i = 0; i < 5; i++) {
        if (heart.num_heart == i)
            hideObject(heart.heart[i]);
    }
    if (heart.num_heart == 0)
        printf("Player is dead. The location of function is MinuxHeart.");
    heart.num_heart--;
}

void InitPlayer() {
    player.obj = createObject(PlayerIdleImages[DirectionOfPlayerFace::DOWN][0]);
    player.scene = gameScene[level];
    player.state = PlayerState::IDLE;
    player.direction = DirectionOfPlayerFace::DOWN;
    player.image_frame = 0;
    player.image_frame_counter = 0;
    player.speed = PLAYER_BASIC_SPEED;
    player.x = 0;
    player.y = 0;
    locateObject(player.obj, gameScene[level], PLAYER_X, PLAYER_Y);
    scaleObject(player.obj, PLAYER_SCALE);
    showObject(player.obj);

    player_timer = createTimer(0.01f);
    startTimer(player_timer);

    moveAnimationTimer = createTimer(0.01f);
}

bool IsOutOfMap()
{
    Coord player_loc = { PLAYER_BASIC_X, PLAYER_BASIC_Y };

    for (int y = 0; y <= BASE_Y; ++y)
    {
        for (int x = 0; x <= BASE_X; ++x)
        {
            if (base[level][y][x]) continue;

            Coord points[4] = { 0 };
            Coord d_coord = { player.x, player.y };
            points[0] = TransformCoord({ x, y }, { 0, 0 }, d_coord);
            points[1] = TransformCoord({ x, y }, { 0, CHUNK_SIZE - 1 }, d_coord);
            points[2] = TransformCoord({ x, y }, { CHUNK_SIZE - 1, CHUNK_SIZE - 1 }, d_coord);
            points[3] = TransformCoord({ x, y }, { CHUNK_SIZE - 1, 0 }, d_coord);

            points[0].x += TILE_WIDTH_OFFSET_FROM_LEFT;
            points[0].y += TILE_SIZE * 1.5;
            points[1].x += TILE_WIDTH_OFFSET_FROM_LEFT + 21 * SCALE / 2;
            points[1].y += TILE_SIZE;
            points[2].x += TILE_SIZE;
            points[2].y += TILE_SIZE * 1.5;
            points[3].x += TILE_SIZE;
            points[3].y += TILE_SIZE * 1.5;

            //// For square tile
            //points[1].y += TILE_HEIGHT;
            //points[2].x += TILE_WIDTH;
            //points[2].y += TILE_HEIGHT;
            //points[3].x += TILE_WIDTH;

            if (IsCollision(player_loc, 4, points))
                return true;
        }
    }

    return false;
}

void ResetPlayer() {
    setObjectImage(player.obj, PlayerIdleImages[DirectionOfPlayerFace::DOWN][0]);
    player.scene = gameScene[level];
    player.state = PlayerState::IDLE;
    player.direction = DirectionOfPlayerFace::DOWN;
    player.image_frame = 0;
    player.image_frame_counter = 0;
    player.speed = PLAYER_BASIC_SPEED;
    player.x = 0;
    player.y = 0;
    locateObject(player.obj, gameScene[level], PLAYER_X, PLAYER_Y);
    scaleObject(player.obj, PLAYER_SCALE);
    showObject(player.obj);
}

int IsPlayerHitted()
{
    for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
    {
        if (bullets[i].is_deleted)
            continue;
        
        Coord box[] = { 
            {PLAYER_X+120*PLAYER_SCALE, PLAYER_Y+67 * PLAYER_SCALE},
            {PLAYER_X+168*PLAYER_SCALE, PLAYER_Y+67 * PLAYER_SCALE},
            {PLAYER_X+161*PLAYER_SCALE, PLAYER_Y+201 * PLAYER_SCALE},
            {PLAYER_X+134*PLAYER_SCALE, PLAYER_Y+201 * PLAYER_SCALE}
        };

        int x = bullets[i].x;
        int y = bullets[i].y;
        if (IsCollision({ x + 1,y + 8 }, 4, box))
            return i;
    }
    return -1;
}

void PlayerKeyboardCallback(KeyCode code, KeyState state) {
    if (code == KeyCode::KEY_UP_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            player.dy += player.speed;
        else
            player.dy -= player.speed;
    }
    else if (code == KeyCode::KEY_RIGHT_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            player.dx += player.speed;
        else
            player.dx -= player.speed;
    }
    else if (code == KeyCode::KEY_DOWN_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            player.dy -= player.speed;
        else
            player.dy += player.speed;
    }
    else if (code == KeyCode::KEY_LEFT_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            player.dx -= player.speed;
        else
            player.dx += player.speed;
    }
    else if (code == KeyCode::KEY_SPACE)
    {
        if (state == KeyState::KEY_PRESSED)
        {
            player.state = PlayerState::ATTACK;
            player.image_frame = 0;
        }
        return;
    }

    int dx = player.dx, dy = player.dy;
    if (dx < 0 && dy < 0)
        player.direction = DirectionOfPlayerFace::LEFT_DOWN;
    else if (dx < 0 && dy > 0)
        player.direction = DirectionOfPlayerFace::UP_LEFT;
    else if (dx > 0 && dy < 0)
        player.direction = DirectionOfPlayerFace::DOWN_RIGHT;
    else if (dx > 0 && dy > 0)
        player.direction = DirectionOfPlayerFace::RIGHT_UP;
    else if (dx == 0 && dy < 0)
        player.direction = DirectionOfPlayerFace::DOWN;
    else if (dx == 0 && dy > 0)
        player.direction = DirectionOfPlayerFace::UP;
    else if (dx > 0 && dy == 0)
        player.direction = DirectionOfPlayerFace::RIGHT;
    else if (dx < 0 && dy == 0)
        player.direction = DirectionOfPlayerFace::LEFT;

    if (player.state == PlayerState::ATTACK)
        return;

    if (dx == 0 && dy == 0)
        player.state = PlayerState::IDLE;
    else
        player.state = PlayerState::WALK;
}

void RefreshPlayer()
{
    ++player.image_frame_counter;
    if (player.image_frame_counter <= 3)
        return;

    player.image_frame_counter = 0;
    ++player.image_frame;
    switch (player.state)
    {
    case PlayerState::IDLE:
        if (player.image_frame >= NUMBER_OF_PLAYER_IDLE_IMAGE_FOR_EACH_DIR)
            player.image_frame = 0;
        setObjectImage(player.obj, PlayerIdleImages[player.direction][player.image_frame]);
        break;
    case PlayerState::WALK:
        if (player.image_frame >= NUMBER_OF_PLAYER_MOVE_IMAGE_FOR_EACH_DIR)
            player.image_frame = 0;
        setObjectImage(player.obj, PlayerMoveImages[player.direction][player.image_frame]);
        break;
    case PlayerState::ATTACK:
        if (player.image_frame == NUMBER_OF_PLAYER_ATTACK_IMAGE_FOR_EACH_DIR - 5) {
            for (int i = 0; i < MAX_NUMBER_OF_BULLET; i++) {
                if (turrets[level][i].obj == 0)
                    break;
                if (isnearPlayer(player.x, player.y, PlayerRange, i)) {
                    isTurretHitted(i);
                }
            }
        }
        if (player.image_frame >= NUMBER_OF_PLAYER_ATTACK_IMAGE_FOR_EACH_DIR)
        {
            player.image_frame = 0;
            if (!player.dx && !player.dy)
            {
                player.state = PlayerState::IDLE;
            }
            else
            {
                player.state = PlayerState::WALK;
            }
            player.speed = PLAYER_BASIC_SPEED;
        }
        setObjectImage(player.obj, PlayerAttackImages[player.direction][player.image_frame]);
        break;
    }
}

void PlayerTimerCallback(TimerID timer) {
    if (timer == player_timer) {
        if (player.state != PlayerState::ATTACK)
        {
            player.x += player.dx;
            player.y += player.dy;
        }
        MoveMap(player.x, player.y);
        MoveTurret(player.x, player.y);
        RefreshPlayer();
        ShowHeart();
        if (IsOutOfMap() && !isMovingLevel) {
            printf("Out of map: %lld, %ld\n", time(NULL), clock());
            level++;
            level %= MAX_LEVEL;
            isMovingLevel = true;
            MoveLevelAnimation();
        }
        else {
            setTimer(player_timer, 0.01f);
            startTimer(player_timer);
        }

        if (int index_of_bullet = IsPlayerHitted() != -1)
        {
            MinusHeart();
            int dx = PLAYER_BASIC_X - bullets[index_of_bullet].x;
            int dy = PLAYER_BASIC_Y - bullets[index_of_bullet].y;
            double len = sqrt(pow(dx, 2) + pow(dy, 2));
            Vec2d direction_vec = bullets[index_of_bullet].direction_vec;

            float sign_of_f = (direction_vec.x >= 0) ? 1 : -1;
            double move_x = sign_of_f * pow(direction_vec.x, 2) * PLAYER_KNOCKBACK_RATE;
            player.x += move_x;
            sign_of_f = (direction_vec.y >= 0) ? 1 : -1;
            double move_y = sign_of_f * pow(direction_vec.y, 2) * PLAYER_KNOCKBACK_RATE;
            player.y += move_y;

            DeleteBullet(index_of_bullet);

            for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
            {
                if(!bullets[i].is_deleted)
                    MoveBullet(-move_x, -move_y, i);
            }
        }
    }
    if (timer == moveAnimationTimer) {
        cnt++;
        animation1_Y += 10;
        animation2_Y += 10;
        if (animation1_Y >= 720) animation1_Y = -720;
        if (animation2_Y >= 720) animation2_Y = -720;
        locateObject(animation1, moveScene, 0, animation1_Y);
        locateObject(animation2, moveScene, 0, animation2_Y);
        RefreshPlayer();
        if (cnt < 50) {
            setTimer(moveAnimationTimer, 0.01f);
            startTimer(moveAnimationTimer);
        }
        else {
            cnt = 0;
            isMovingLevel = false;
            ResetPlayer();
            setTimer(player_timer, 0.01f);
            startTimer(player_timer);
            enterScene(gameScene[level]);
        }
    }
}

void MoveLevelAnimation() {
    for (int i = 0; i < 5; i++) {
        hideObject(heart.heart[i]);
    }
    locateObject(animation1, moveScene, 0, animation1_Y);
    locateObject(animation2, moveScene, 0, animation2_Y);
    showObject(animation1);
    showObject(animation2);
    setObjectImage(player.obj, PlayerIdleImages[DirectionOfPlayerFace::DOWN][0]);
    player.scene = moveScene;
    player.state = PlayerState::WALK;
    player.direction = DirectionOfPlayerFace::DOWN;
    player.image_frame = 0;
    player.image_frame_counter = 0;
    player.speed = PLAYER_BASIC_SPEED;
    player.x = 0;
    player.y = 0;
    locateObject(player.obj, moveScene, PLAYER_X, PLAYER_Y);
    scaleObject(player.obj, PLAYER_SCALE);
    showObject(player.obj);
    startTimer(moveAnimationTimer);
    heart_function();
    enterScene(moveScene);
}