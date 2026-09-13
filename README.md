# Packaging

ForgeOS packages are called **fpk** files. An `.fpk` is a plain gzip tarball (the extension is a
convention, not a distinct format — GitHub's upload UI is picky about `.fpk`, so files in this
repo are stored as `.tar.gz` and referenced that way in `packages.json`).

## Structure

```
manifest.json
src/       source files
bin/       precompiled objects, if any
```

## Manifest format

```json
{
  "name": "fastfetch",
  "version": "1.0.0",
  "description": "System info splash tool for ForgeOS",
  "author": "projectrivet",
  "type": "kernel-builtin",
  "files": [
    "src/fastfetch.c",
    "src/fastfetch.h"
  ]
}
```

Fields:

| Field | Meaning |
|---|---|
| `name` | Package name, used in `fpkg install <name>` |
| `version` | Semver string |
| `description` | One line, shown in `fpkg list` and the packages page |
| `author` | Maintainer name or handle |
| `type` | `kernel-builtin` (only type that exists today — see below) |
| `files` | Paths inside the tarball, for reference |

## Why `kernel-builtin` is the only package type

ForgeOS doesn't have a userspace, processes, or an ELF loader yet — every shell command runs
inside the kernel binary itself. A package can't ship a standalone executable until that changes.
Instead, installing a `kernel-builtin` package today means:

1. Copy the package's source files into `kernel/`.
2. `#include` its header in `kernel.c` and add one branch to the command dispatcher calling its
   entry function.
3. Add the new `.c` file to `build/build.sh`'s compile step and link step.
4. Rebuild: `bash build/build.sh`.

This will stop being necessary once ForgeOS has a real userspace (see the main README's roadmap).

## The repo index — `packages.json`

All available packages are listed in a single file at the repo root:

```json
{
  "repo_name": "forge-packages",
  "maintainer": "projectrivet",
  "updated": "2026-09-13",
  "packages": [
    {
      "name": "fastfetch",
      "version": "1.0.0",
      "description": "System info splash tool for ForgeOS",
      "url": "https://forge0s.github.io/forge-packages/packages/fastfetch.tar.gz",
      "sha256": "4b1d15a7e808c7ecdba9901abadfe6963f05c6150bf886b47942e9b70c8e7724",
      "type": "kernel-builtin"
    }
  ]
}
```

`fpkg install <name>` is designed to fetch this file, find the matching entry, download the
tarball, verify the sha256 checksum, and extract it — once ForgeOS has a network stack. Right
now `fpkg` is a stub that explains this plan when you run it.

## Publishing a package

1. Build your tarball with a `manifest.json` at its root:
   ```bash
   tar czf mypackage.tar.gz manifest.json src bin
   sha256sum mypackage.tar.gz
   ```
2. Commit the tarball to `packages/` in this repo.
3. Add an entry to `packages.json` with the download URL (pointing at the GitHub Pages URL or a
   GitHub Release asset) and the sha256 checksum from step 1.
4. Push. GitHub Pages serves the update within about a minute — no build step, no approval queue.

## Hosting this repo for free

This repo itself is the hosting — no domain purchase, no separate hosting bill required:

1. Make the repo public.
2. Go to **Settings → Pages**, set the source to the `main` branch, root folder.
3. GitHub serves everything at `https://<username>.github.io/<repo>/`, permanently and for free.
4. For large binaries, prefer attaching them to a **GitHub Release** over committing them
   directly — same free hosting, better suited to binary assets, and keeps the repo small.
