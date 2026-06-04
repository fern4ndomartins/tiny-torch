---
type: pm4_packet
opcode: 0x37
name: WRITE_DATA
hw_blocks: [GFX, SDMA, Compute]
---

# WRITE_DATA (`0x37`)

Writes arbitrary data to GPU memory or a register. Used for command buffer patching, timestamp queries, and ring buffer updates.

## Packet layout

```mermaid
bitfield
title WRITE_DATA (4 DWORDs + optional payload)
"31" : "30" : "29..28" : "27" : "26..0"
"WRITE_CONFIRM" : "ENGINE_SEL" : "DST_SEL" : "WRITE_ONE_REG" : "RESERVED"