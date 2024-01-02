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
        min_set = [0, 0, 0]
        game_id_pos = len('Game ')
        m = re.match('\d+',line[game_id_pos:-1])
        game_id = int(m[0])

        # index of the character after the game id
        set_info_pos = game_id_pos + len(m[0]) + 2
        sets = line[set_info_pos:-1].split(';')
        for set in sets:
            r,g,b = (0,0,0)
            m_r = re.search('(\d+) red', set)
            m_g = re.search('(\d+) green', set)
            m_b = re.search('(\d+) blue', set)

            if m_r:
                r = int(m_r[1])
                if min_set[0] < r:
                    min_set[0] = r
            if m_g:
                g = int(m_g[1])
                if min_set[1] < g:
                    min_set[1] = g
            if m_b:
                b = int(m_b[1])
                if min_set[2] < b:
                    min_set[2] = b


            print(f"{game_id} {r} {g} {b} {min_set}")

        power = min_set[0] * min_set[1] * min_set[2]
        sum += power
        print(f"{game_id}: {min_set[0]} * {min_set[1]} * {min_set[2]} {power} Sum: {sum}")

print("----------------------------")
print(sum)
