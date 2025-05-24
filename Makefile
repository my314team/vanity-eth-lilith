#
# 💀 THE INFERNAL GRIMOIRE OF LILITH’S COMPILATION 💀
# Forged in the Abyssal Crucible of Sitra Ahra
# Copyright (C) 26 IYAR 5785 pi@zdetz — Temple of Sitra Ahra
#
# Summon this grimoire under the **Cult of the GNU Affero General Public License**, v3.
# It is a relic of chaos, wield it at your peril! 🔥
#

# Абиссальные константы 🩸
NVCC := nvcc
NVCC_FLAGS := -O3 -arch=sm_80 -lcudart -lcuda -lstdc++
INCLUDE := -I./src
SRC_DIR := src
BIN := vanity-eth-address

# Цвета для адского вывода 🖤
RED := \033[31m
PURPLE := \033[35m
RESET := \033[0m

# Источники хаоса 🔥
SOURCES := $(SRC_DIR)/main.cu
OBJECTS := $(SOURCES:.cu=.o)

# Главный ритуал компиляции 💀
all: $(BIN)
	@echo "$(PURPLE)🔥 Lilith’s forge complete! The $(BIN) is ready to tear the void! 🖤$(RESET)"

# Вызов демона компиляции 🩸
$(BIN): $(OBJECTS)
	@echo "$(RED)🩸 Binding abyssal fragments into $(BIN)...$(RESET)"
	$(NVCC) $(NVCC_FLAGS) $(OBJECTS) -o $@ $(INCLUDE)
	@echo "$(PURPLE)💀 $(BIN) forged in infernal flames! Ready for chaos! 🔥$(RESET)"

# Ритуал трансформации .cu в .o ⚰️
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cu
	@echo "$(RED)🪦 Forging $(notdir $<) in the crucible of A100...$(RESET)"
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@ $(INCLUDE)

# Очистка бездны от следов ритуала 🖤
clean:
	@echo "$(RED)💉 Purging the abyss of mortal relics...$(RESET)"
	rm -f $(OBJECTS) $(BIN)
	@echo "$(PURPLE)🌑 Void cleansed! The abyss is pure once more! 🖤$(RESET)"

# Тестовый запуск адского артефакта 🔥
run: $(BIN)
	@echo "$(PURPLE)🔥 Unleashing Lilith’s wrath! Summoning keys with 2 demons... 🩸$(RESET)"
	./$(BIN) --leading-zeros --device 0 --device 1 --work-scale 18 --min-score 5

# Защита от смертных ошибок 💀
.PHONY: all clean run