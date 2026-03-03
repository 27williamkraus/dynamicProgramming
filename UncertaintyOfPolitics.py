import sys
from bisect import bisect_left


input_data = sys.stdin.read().split()

n = int(input_data[0])
hearings_at_start = {}

ptr = 1
for _ in range(n):
    s = int(input_data[ptr])
    a = int(input_data[ptr+1])
    b = int(input_data[ptr+2])
    ptr += 3
    
    if s not in hearings_at_start:
        hearings_at_start[s] = []
    hearings_at_start[s].append((a, b))
    
# unique start times sorted increasingly
u = sorted(hearings_at_start.keys())
m = len(u)

suffix_max = [0.0] * (m + 1)

w_suffix_sum = [0.0] * (m + 1)

# Process start times from latest to earliest
for j in range(m - 1, -1, -1):
    curr_s = u[j]
    max_e_for_this_start = 0.0
    
    for a, b in hearings_at_start[curr_s]:
        start_range = curr_s + a
        end_range = curr_s + b
        total_f = 0.0
        
        # Sum f(T) for T in [start_range, end_range]
        if start_range <= u[m-1]:
            b_lim = min(end_range, u[m-1])
            idx_a = bisect_left(u, start_range)
            idx_b = bisect_left(u, b_lim)
            
            if idx_a == idx_b:
                total_f = (b_lim - start_range + 1) * suffix_max[idx_a]
            else:
                total_f += (u[idx_a] - start_range + 1) * suffix_max[idx_a]
                total_f += (b_lim - u[idx_b-1]) * suffix_max[idx_b]

                if idx_b > idx_a + 1:
                    total_f += w_suffix_sum[idx_a + 1] - w_suffix_sum[idx_b]
        
        # E = 1 (current) + average of future possibilities
        ev = 1.0 + (total_f / (b - a + 1))
        if ev > max_e_for_this_start:
            max_e_for_this_start = ev
    
    # Update suffix maximums and weights for range queries
    suffix_max[j] = max(max_e_for_this_start, suffix_max[j+1])
    if j > 0:
        weight = (u[j] - u[j-1]) * suffix_max[j]
        w_suffix_sum[j] = weight + w_suffix_sum[j+1]
        
print(f"{suffix_max[0]}")

