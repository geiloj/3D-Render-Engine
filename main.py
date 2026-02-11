import sys

if len(sys.argv) < 3:
    print("Usage: python obj_to_header.py input.obj output.h")
    sys.exit(1)

obj_file  = sys.argv[1]
hdr_file  = sys.argv[2]

verts = []
faces = []

with open(obj_file, 'r') as f:
    for line in f:
        line = line.strip()
        if not line or line.startswith('#'):
            continue

        parts = line.split()
        if parts[0] == 'v':
            # vertex position
            x,y,z = parts[1], parts[2], parts[3]
            verts.append((float(x), float(y), float(z)))
        elif parts[0] == 'f':
            # face indices
            # each face part might be "v", "v/vt", "v//vn", or "v/vt/vn"
            idxs = []
            for p in parts[1:]:
                vnum = p.split('/')[0]
                idxs.append(int(vnum) - 1)  # OBJ indexing is 1-based
            # triangulate if necessary
            if len(idxs) == 3:
                faces.append((idxs[0], idxs[1], idxs[2]))
            else:
                # simple fan triangulation
                for i in range(1, len(idxs)-1):
                    faces.append((idxs[0], idxs[i], idxs[i+1]))

with open(hdr_file, 'w') as out:
    out.write("#pragma once\n")
    out.write('#include "Point.h"\n\n')

    # write vertices
    out.write(f"inline struct Point vertices[{len(verts)}] = {{\n")
    for (x,y,z) in verts:
        out.write(f"    {{{x}, {y}, {z}}},\n")
    out.write("};\n\n")

    # write face indices
    out.write(f"inline const int faces[{len(faces)}][3] = {{\n")
    for (a,b,c) in faces:
        out.write(f"    {{{a},{b},{c}}},\n")
    out.write("};\n")

print(f"Export complete: {hdr_file} ({len(verts)} verts, {len(faces)} triangles)")
