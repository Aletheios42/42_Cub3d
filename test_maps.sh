#!/bin/bash

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Directorios de mapas
INVALID_MAPS_DIR="invalidMaps"
VALID_MAPS_DIR="maps"

# Compilar el proyecto
echo -e "${YELLOW}Compilando cub3d...${NC}"
make
if [ $? -ne 0 ]; then
    echo -e "${RED}Error de compilación${NC}"
    exit 1
fi

# Mapas inválidos esperados (deben fallar)
declare -A invalid_maps=(
    ["01.cub"]="mapa fragmentado"
    ["02.cub"]="textuta WE empieza por espacios"
    ["03.cub"]="mapa abierto"
    ["04.cub"]="textura WE duplicada"
    ["05.cub"]="falta textura WE"
    ["06.cub"]="textura SO duplicada"
    ["07.cub"]="falta archivo textura EA"
    ["08.cub"]="mala extensión textura WE"
    ["09.cub"]="no existe archivo textura EA"
    ["10.cub"]="falta color del techo"
    ["11.cub"]="color del suelo duplicado"
    ["12.cub"]="suelo no tiene color"
    ["13.cub"]="color del suelo inválido"
    ["14.cub"]="letras inválidas después de color"
    ["15.cub"]="no tiene mapa"
    ["16.cub"]="mapa abierto (flood fill)"
    ["17.cub"]="no hay jugador"
    ["18.cub"]="hay 3 jugadores"
    ["19.cub"]="hay 2 jugadores"
)

# Contadores
total=0
passed=0
failed=0

echo -e "\n${BLUE}Testing mapas INVÁLIDOS (deben fallar):${NC}\n"

# Testear mapas inválidos
for map in "${!invalid_maps[@]}"; do
    if [ -f "$INVALID_MAPS_DIR/$map" ]; then
        total=$((total + 1))
        echo -n "Testing $map (${invalid_maps[$map]})... "
        
        # Ejecutar cub3d y capturar exit code
        ./cub3d "$INVALID_MAPS_DIR/$map" > /dev/null 2>&1
        exit_code=$?
        
        if [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}PASS (falló correctamente)${NC}"
            passed=$((passed + 1))
        else
            echo -e "${RED}FAIL (debería haber fallado)${NC}"
            failed=$((failed + 1))
        fi
    else
        echo -e "${YELLOW}WARNING: $INVALID_MAPS_DIR/$map no encontrado${NC}"
    fi
done

echo -e "\n${BLUE}Testing otros mapas:${NC}\n"

# Testear mapas restantes (cardinal.cub, tiny.cub, etc.)
for map in $VALID_MAPS_DIR/*.cub; do
    basename_map=$(basename "$map")
    
    # Saltar si ya fue testeado como inválido
    if [[ -v invalid_maps["$basename_map"] ]]; then
        continue
    fi
    
    if [ -f "$map" ]; then
        total=$((total + 1))
        echo -n "Testing $basename_map... "
        
        ./cub3d "$map" > /dev/null 2>&1
        exit_code=$?
        
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}PASS${NC}"
            passed=$((passed + 1))
        else
            echo -e "${RED}FAIL (exit code: $exit_code)${NC}"
            failed=$((failed + 1))
        fi
    fi
done

# Resultados finales
echo -e "\n${YELLOW}Resultados:${NC}"
echo -e "Total: $total"
echo -e "${GREEN}Passed: $passed${NC}"
echo -e "${RED}Failed: $failed${NC}"

if [ $failed -eq 0 ]; then
    echo -e "\n${GREEN}¡Todos los tests pasaron correctamente!${NC}"
else
    echo -e "\n${RED}$failed tests fallaron${NC}"
fi
