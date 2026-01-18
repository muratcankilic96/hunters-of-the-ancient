#include "global.h"
#include "strings.h"
#include "string_util.h"
#include "characters.h"
#include "team_rocket_rank.h"

static const u8 *const gTeamRocketRankStringPtrs[TEAM_ROCKET_RANK_COUNT] = {
    [TEAM_ROCKET_RANK_UNREGISTERED] = gTeamRocketRankString_Unregistered,
    [TEAM_ROCKET_RANK_RECRUIT] = gTeamRocketRankString_Recruit,
    [TEAM_ROCKET_RANK_MEMBER] = gTeamRocketRankString_Member,
    [TEAM_ROCKET_RANK_AGENT] = gTeamRocketRankString_Agent,
    [TEAM_ROCKET_RANK_OFFICER] = gTeamRocketRankString_Officer,
    [TEAM_ROCKET_RANK_EXECUTIVE] = gTeamRocketRankString_Executive,
    [TEAM_ROCKET_RANK_BOSS] = gTeamRocketRankString_Boss
};

static const u8 gTeamRocketRankString_Unregistered[] = _("-");
static const u8 gTeamRocketRankString_Recruit[] = _("RECRUIT");
static const u8 gTeamRocketRankString_Member[] = _("MEMBER");
static const u8 gTeamRocketRankString_Agent[] = _("AGENT");
static const u8 gTeamRocketRankString_Officer[] = _("OFFICER");
static const u8 gTeamRocketRankString_Executive[] = _("EXECUTIVE");
static const u8 gTeamRocketRankString_Boss[] = _("BOSS");

u8 *GetTeamRocketRankString(u8 *dst0, u8 rankId) {
    return StringCopy(dst0, gTeamRocketRankStringPtrs[rankId]);
}