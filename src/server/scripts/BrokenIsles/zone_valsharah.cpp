/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 * This file is part of the LegionEmulation Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Creature.h"
#include "Spell.h"
#include "Vehicle.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"

namespace CenariusKeeper
{
    enum QuestIds
    {
        QUEST_CENARIUS_KEEPER_OF_THE_GROVE = 40122,
    };

    enum CreatureIds
    {
        NPC_MALFURION_STORMRAGE             = 91462,
        NPC_MALFURION_SUMMON                = 91465,
        NPC_NYANDRA                         = 91652,
        NPC_KILLCREDIT_SPEAK_TO_MALFURION   = 91461,
    };

    enum SpellIds
    {
        SPELL_SUMMON_MALFURION             = 181481,
        SPELL_RIDE_VEHICLE_HARDCODED       = 46598,
        SPELL_UPDATE_ZONE_AURAS            = 84034,
        SPELL_TRANSFORM_MALFURION_STAG     = 185846,
        SPELL_REVERSE_CAST_RIDE_SEAT_1     = 88885,
        SPELL_RIDE_VEHICLE                 = 52391,
        SPELL_REVERSE_CAST_SUMMON_NYANDRA  = 187438,
        SPELL_TRANSFORM_MALFURION          = 181483,
        SPELL_SUMMON_NYANDRA               = 181879,
        SPELL_CENARIUS_PLIGHT_CONVERSATION = 181485, // Play Conversation (352)
    };

    enum TextIds
    {
        SAY_AHH_VALSHARAH       = 0,
        SAY_EVERY_STEP          = 1,
        SAY_AGES_AGO            = 2,
        SAY_MERELY_AN_ECHO      = 3,
        SAY_MAKE_READY          = 4,
        SAY_FOLLOW_ME           = 5,
    };

    enum Events
    {
        EVENT_START_TRAVEL      = 1,
        EVENT_TALK_EVERY_STEP   = 2,
        EVENT_TALK_AGES_AGO     = 3,
        EVENT_TALK_MERELY_ECHO  = 4,
        EVENT_TALK_MAKE_READY   = 5,
        EVENT_EJECT_PLAYER      = 6,
        EVENT_NYANDRA_SEQUENCE  = 7,
        EVENT_NYANDRA_FOLLOW    = 8,
        EVENT_NYANDRA_STOP      = 9,
        EVENT_KNEEL             = 10,
    };

    enum Etc
    {
        WP_END,
    };

    uint32 const malfurionpathSize = 19;
    Position const malfurionPathToGrove[malfurionpathSize] =
    {
        { 2291.4734f, 6597.7544f, 138.30594f, 0.0f },
        { 2297.9734f, 6634.7544f, 135.05594f, 0.0f },
        { 2324.4734f, 6661.7544f, 134.05594f, 0.0f },
        { 2333.4734f, 6670.0044f, 135.05594f, 0.0f },
        { 2355.2234f, 6668.2544f, 138.80594f, 0.0f },
        { 2370.7234f, 6663.7544f, 140.80594f, 0.0f },
        { 2383.4734f, 6662.0044f, 141.80594f, 0.0f },
        { 2397.9734f, 6658.2544f, 140.30594f, 0.0f },
        { 2412.9734f, 6650.0044f, 138.80594f, 0.0f },
        { 2424.7234f, 6636.7544f, 140.05594f, 0.0f },
        { 2450.7234f, 6615.2544f, 136.55594f, 0.0f },
        { 2470.2234f, 6594.0044f, 135.30594f, 0.0f },
        { 2498.4734f, 6590.2544f, 134.30594f, 0.0f },
        { 2534.4734f, 6594.2544f, 132.30594f, 0.0f },
        { 2572.2234f, 6609.5044f, 127.30595f, 0.0f },
        { 2601.9734f, 6634.5044f, 119.80595f, 0.0f },
        { 2614.7234f, 6656.7544f, 113.05595f, 0.0f },
        { 2614.7234f, 6679.2544f, 108.05595f, 0.0f },
        { 2609.1667f, 6704.6987f, 104.28856f, 0.0f },
    };

    uint32 const malfurionpathSize1 = 14;
    Position const malfurionPathtoNyandra[malfurionpathSize1] =
    {
        { 2610.267f, 6700.865f, 104.83893f, 0.0f },
        { 2610.017f, 6701.865f, 105.08893f, 0.0f },
        { 2609.767f, 6703.365f, 104.83893f, 0.0f },
        { 2610.017f, 6704.865f, 104.83893f, 0.0f },
        { 2610.017f, 6706.365f, 105.08893f, 0.0f },
        { 2610.017f, 6709.115f, 104.83893f, 0.0f },
        { 2609.767f, 6710.615f, 105.08893f, 0.0f },
        { 2610.017f, 6715.115f, 104.83893f, 0.0f },
        { 2610.017f, 6715.615f, 104.58893f, 0.0f },
        { 2610.017f, 6716.615f, 104.58893f, 0.0f },
        { 2609.267f, 6717.615f, 104.83893f, 0.0f },
        { 2608.767f, 6718.865f, 104.83893f, 0.0f },
        { 2608.517f, 6720.865f, 104.83893f, 0.0f },
        { 2606.8586f, 6724.6426f, 104.887665f, 0.0f },
    };
};




void AddSC_valsharah()
{

}
