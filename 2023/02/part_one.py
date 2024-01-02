import re
from pathlib import Path

input_path = (Path(__file__)
              .parent
              .joinpath("input.txt")
            )

max_red = 12
max_green = 13
max_blue = 14

sum = 0

with open(input_path) as file:

    for line in file:
        game_id_pos = len('Game ')
        m = re.match('\d+',line[game_id_pos:-1])
        game_id = int(m[0])

        # index of the character after the game id
        set_info_pos = game_id_pos + len(m[0]) + 2
        sets = line[set_info_pos:-1].split(';')
        all_sets_ok = True
        for set in sets:
            r,g,b = (0,0,0)
            m_r = re.search('(\d+) red', set)
            m_g = re.search('(\d+) green', set)
            m_b = re.search('(\d+) blue', set)

            if m_r:
                r = int(m_r[1])
            if m_g:
                g = int(m_g[1])
            if m_b:
                b = int(m_b[1])

            valid = r <= max_red and g <= max_green and b <= max_blue

            if not valid:
                all_sets_ok = False

            print(f"{game_id} {r} {g} {b} {valid} {all_sets_ok}")

        if all_sets_ok:
            sum += game_id
            print(f"Game {game_id} is valid: Sum: {sum}")
        else:
            print(f"Game {game_id} is NOT valid")


print("------------------------")
print(sum)
