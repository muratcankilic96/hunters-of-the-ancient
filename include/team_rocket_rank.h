#ifndef GUARD_TEAM_ROCKET_RANK_H
#define GUARD_TEAM_ROCKET_RANK_H

#include "global.h"

#define TEAM_ROCKET_RANK_UNREGISTERED   0
#define TEAM_ROCKET_RANK_RECRUIT        1
#define TEAM_ROCKET_RANK_MEMBER         2
#define TEAM_ROCKET_RANK_AGENT          3
#define TEAM_ROCKET_RANK_OFFICER        4
#define TEAM_ROCKET_RANK_EXECUTIVE      5
#define TEAM_ROCKET_RANK_UNDERBOSS      6
#define TEAM_ROCKET_RANK_COUNT          7

static const u8 gTeamRocketRankString_Unregistered[];
static const u8 gTeamRocketRankString_Recruit[];
static const u8 gTeamRocketRankString_Member[];
static const u8 gTeamRocketRankString_Agent[];
static const u8 gTeamRocketRankString_Officer[];
static const u8 gTeamRocketRankString_Executive[];
static const u8 gTeamRocketRankString_Underboss[];

static const u8 *const gTeamRocketRankStringPtrs[TEAM_ROCKET_RANK_COUNT];

u8 *GetTeamRocketRankString(u8 *);

#endif // GUARD_TEAM_ROCKET_RANK_H
