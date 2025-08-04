#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

MAPS_DIR="maps"

# Mapas inválidos con prefijo "invalid" y su descripción
declare -A invalid_maps=(
    ["invalid01.cub"]="mapa fragmentado"
    ["invalid02.cub"]="textura WE empieza por espacios"
    ["invalid03.cub"]="mapa abierto"
    ["invalid04.cub"]="textura WE duplicada"
    ["invalid05.cub"]="falta textura WE"
    ["invalid06.cub"]="textura SO duplicada"
    ["invalid07.cub"]="falta archivo textura EA"
    ["invalid08.cub"]="mala extensión textura WE"
    ["invalid09.cub"]="no existe archivo textura EA"
    ["invalid10.cub"]="falta color del techo"
    ["invalid11.cub"]="color del suelo duplicado"
    ["invalid12.cub"]="suelo no tiene color"
    ["invalid13.cub"]="color del suelo inválido"
    ["invalid14.cub"]="letras inválidas después de color"
    ["invalid15.cub"]="no tiene mapa"
    ["invalid16.cub"]="mapa abierto (flood fill)"
    ["invalid17.cub"]="no hay jugador"
    ["invalid18.cub"]="hay 3 jugadores"
    ["invalid19.cub"]="hay 2 jugadores"
    ["invalidcardinal.cub"]="cardinal inválido"
    ["invalidtiny.cub"]="tiny inválido"
)

total=0
passed=0
failed=0

echo -e "\n${BLUE}Testing mapas INVÁLIDOS (deben fallar):${NC}\n"
for map in "${!invalid_maps[@]}"; do
    if [ -f "$MAPS_DIR/$map" ]; then
        total=$((total + 1))
        echo -n "Testing $map (${invalid_maps[$map]})... "
        ./cub3d "$MAPS_DIR/$map" > /dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo -e "${GREEN}PASS (falló correctamente)${NC}"
            passed=$((passed + 1))
        else
            echo -e "${RED}FAIL (debería haber fallado)${NC}"
            failed=$((failed + 1))
        fi
    else
        echo -e "${YELLOW}WARNING: $MAPS_DIR/$map no encontrado${NC}"
    fi
done

echo -e "\n${BLUE}Testing mapas VÁLIDOS (deben pasar):${NC}\n"
for map in "$MAPS_DIR"/*.cub; do
    filename=$(basename "$map")
    if [[ $filename != invalid* ]]; then
        total=$((total + 1))
        echo -n "Testing $filename... "
        ./cub3d "$MAPS_DIR/$filename" > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}PASS${NC}"
            passed=$((passed + 1))
        else
            echo -e "${RED}FAIL (debería haber pasado)${NC}"
            failed=$((failed + 1))
        fi
    fi
done

echo -e "\n${YELLOW}Resultados:${NC}"
echo -e "Total: $total"
echo -e "${GREEN}Passed: $passed${NC}"
echo -e "${RED}Failed: $failed${NC}"

if [ $failed -eq 0 ]; then
    echo -e "\n${GREEN}¡Todos los tests pasaron correctamente!${NC}"
else
    echo -e "\n${RED}$failed tests fallaron${NC}"
fi
