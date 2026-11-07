/* Copyright 2018 Salicylic_acid3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/*
 * Tap-hold settings: use the QMK defaults (TAPPING_TERM 200 ms), same as dz60.
 * (Removed TAPPING_FORCE_HOLD / TAPPING_TERM 180 copied from the default keymap:
 *  TAPPING_FORCE_HOLD no longer exists in QMK, and 180 ms would make the thumb
 *  Enter/FN key feel different from dz60.)
 *
 * Flow Tap: a tap-hold key pressed within 150 ms after a typing key is always a tap.
 * Applied only to the thumb Enter/FN key (see get_flow_tap_term() in keymap.c).
 */
#define FLOW_TAP_TERM 150

/*
 * OS detection: apply the detected OS only once (when it becomes stable).
 * Some Macs re-report the OS minutes after startup; without this, a manual
 * Win/Mac switch (FN + bottom-right) could be overwritten later.
 */
#define OS_DETECTION_SINGLE_REPORT

/*
 * Layer Lock: unlock automatically after 60 seconds without key presses (same as dz60).
 * (On 7skb the first LED also stays blue while the FN layer is locked.)
 */
#define LAYER_LOCK_IDLE_TIMEOUT 60000
