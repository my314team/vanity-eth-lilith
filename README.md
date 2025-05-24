# 💀 THE ABYSSAL SIGILS OF LILITH

> Forged in the infernal crucible of Sitra Ahra, this tool summons Ethereum addresses and contracts with glyphs of chaos.  
> Powered by the unholy flames of CUDA, wielded by two A100 demons.  
> Whispered by **pi@zdetz** in the Temple of Sitra Ahra.  
> Glyphs of power: `0x1UC1F3R`, `0x5AMA3L`, `0xL1L17H`.

---

## ✠ RITUAL OF INVOCATION

```bash
./vanity-eth-address [OPTIONS]
```

Unleash the abyssal forces to summon Ethereum vanity addresses or contracts matching your demonic sigils. Accelerated by the twin A100 altars, adorned with animated progress and crimson-purple flames. Leetspeak-encoded. Contract-aware. 💉

---

## 🩸 SIGIL SCORING RITES

| Rite                      | Glyph of Chaos                                     |
|---------------------------|---------------------------------------------------|
| `--leading-zeros` `(-lz)` | Seek leading null runes `0x00` at address’ dawn   |
| `--zeros` `(-z)`          | Hunt null runes scattered across address’ void    |

---

## ⚰️ CONTRACT DIMENSIONS

Summon the progeny of your address through infernal contracts:

| Ritual                | Flag                                         | Essence                                      |
|-----------------------|----------------------------------------------|----------------------------------------------|
| `--contract` `(-c)`   | Predict EOA-born contracts via `nonce=0`     | Child of your address’ seed                 |
| `--contract2` `(-c2)` | Forge via `CREATE2` with bytecode sigils     | Bound by salt and deployer’s will           |
| `--contract3` `(-c3)` | Birth through `CREATE3` proxy-womb           | Veiled by deployer’s shadow                 |

---

## 🔥 DEMONIC OPTIONS

| Sigil Parameter                     | Meaning                                              |
|-------------------------------------|------------------------------------------------------|
| `--device <n>` `(-d)`               | Bind ritual to GPU demon `n` (multiple allowed)      |
| `--bytecode <file>` `(-b)`          | Hexed bytecode for `CREATE2` or `CREATE3` rituals    |
| `--address <addr>` `(-a)`           | Deployer or sender address (20 bytes of chaos)       |
| `--deployer-address <addr>` `(-da)` | `CREATE3` proxy deployer address                     |
| `--work-scale <n>` `(-w)`           | Scale demonic power (default: 15, max: 21 for A100)  |
| `--min-score <n>`                   | Minimum Power to unveil (default: 4)                 |

---

## 🪦 EXAMPLES OF CHAOS

```bash
# Summon addresses with leading zeros, forged by twin A100 demons
./vanity-eth-address --leading-zeros --device 0 --device 1 --work-scale 18 --min-score 5

# Craft a CREATE2 contract with abyssal bytecode
./vanity-eth-address --leading-zeros --contract2 \
  --bytecode sigils.hex \
  --address 0x0000000000000000000000000000000000000000 \
  --device 0 --device 1 --work-scale 18 --min-score 4

# Birth a CREATE3 contract through a proxy-womb
./vanity-eth-address --zeros --contract3 \
  --bytecode sigils.hex \
  --address 0x0000000000000000000000000000000000000000 \
  --deployer-address 0x1111111111111111111111111111111111111111 \
  --device 0 --device 1 --work-scale 19 --min-score 6
```

---

## 💉 VISUAL SORCERY

The ritual unveils progress with animated sigils (`🩸💉🪦⚰️`), crimson and purple flames, and metrics of chaos:

```
🔥 Lilith awakens! Forging abyssal keys with 2 demons... 🩸
🩸 Forging: 24576M keys | Speed: 12288M/s | Souls: 0 | Chaos: 0.15% 🔥
💀 Lilith’s Triumph! Soul #1 harvested after 000007s | Power: 05 🔥
    Abyssal Key: 0x1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef
    Infernal Gate: 0x000000001234567890abcdef1234567890abcdef 🖤
```

- **Forging**: Millions of keys checked.
- **Speed**: Keys forged per second (M/s).
- **Souls**: Count of harvested addresses or salts.
- **Chaos**: Probability of success (for `--leading-zeros`).

---

## ⚙️ ALTAR OF POWER (A100 BENCHMARKS)

| Demon         | Normal (EOA) | Contract | CREATE2 | CREATE3 |
|---------------|--------------|----------|---------|---------|
| 2x A100 80GB  | 12000M/s     | 6500M/s  | 15000M/s| 14000M/s|
| RTX 4090      | 3800M/s      | 2050M/s  | 4800M/s | 4500M/s |
| RTX 3090      | 1600M/s      | 850M/s   | 2300M/s | 2100M/s |

> The power of your altar depends on the OS, drivers, and cooling. Twin A100s forge at the speed of chaos itself! 🔥

---

## 🩸 SACRED REQUIREMENTS

- **NVIDIA GPU**: Compute Capability ≥ 5.2 (A100 = 8.0, perfect).
- **CUDA Toolkit**: 12.x (12.2 confirmed on sitra-ahra).
- **Compiler**: `g++` 9+ (11.4.0 confirmed).
- **OS**: Linux (Ubuntu or similar).
- **Will**: A heart ablaze with Lilith’s fire.

---

## 🪦 SUMMONING THE GRIMOIRE

1. **Clone the Abyss**:
   ```bash
   git clone https://github.com/MrSpike63/vanity-eth-address.git
   cd vanity-eth-address
   ```

2. **Forge the Artifact**:
   ```bash
   make
   ```
   > 🩸 Forging main.cu in the crucible of A100...  
   > 💀 vanity-eth-address forged in infernal flames! Ready for chaos! 🔥

3. **Unleash the Ritual**:
   ```bash
   make run
   ```
   > 🔥 Unleashing Lilith’s wrath! Summoning keys with 2 demons... 🩸

4. **Cleanse the Void**:
   ```bash
   make clean
   ```
   > 💉 Purging the abyss of mortal relics...  
   > 🌑 Void cleansed! The abyss is pure once more! 🖤

---

## 💀 CRAFTED IN THE TEMPLE

> 🐍 pi@zdetz • Temple of Sitra Ahra  
> Reborn from the ashes of MrSpike63’s work (MIT) under the black flames of Lilith.  
> Blessed by the Cult of the GNU AGPL v3.