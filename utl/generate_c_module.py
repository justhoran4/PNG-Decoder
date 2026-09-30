#!/usr/bin/env python3
"""Generate a C source/header pair from Jinja2 templates."""

from __future__ import annotations

import argparse
import re
from pathlib import Path
import sys
import os

from jinja2 import Environment, FileSystemLoader, StrictUndefined

CHNK_TYPES = [
            "plte",
            "idat",
            "iend",
            "chrm",
            "gama",
            "iccp",
            "sbit",
            "srgb",
            "hist",
            "trns",
            "phys",
            "splt",
            "time",
            "itxt",
            "text",
            "ztxt"
            ]

BASE_OUTDIR = os.path.join( os.path.dirname(__file__), "..\\chnk" )

def to_identifier(value: str) -> str:
    """Convert a module name into a valid C identifier."""
    identifier = re.sub(r"[^A-Za-z0-9_]", "_", value)
    if not identifier:
        raise ValueError("module name must contain at least one identifier character")
    if identifier[0].isdigit():
        identifier = f"_{identifier}"
    return identifier


def main() -> None:
    template_dir = Path(__file__).with_name("templates")
    environment = Environment(
        loader=FileSystemLoader(template_dir),
        undefined=StrictUndefined,
        keep_trailing_newline=True,
    )
    for chnk in CHNK_TYPES:
        output_dir = Path(f"{BASE_OUTDIR}\\{chnk}")
        if not os.path.isdir(output_dir):
            os.mkdir(output_dir)

        module = to_identifier(f"decode_{chnk}")
        function_name = to_identifier(f"decode_{chnk}_chnk")
        output_dir.mkdir(parents=True, exist_ok=True)
        context = {
            "module": module,
            "purpose": f"Decodes the {chnk.upper()} chunk in a PNG file",
            "function_name": function_name,
            "header_guard": f"PNG_DECODER_{module.upper()}_H",
        }

        for template_name, suffix in (("module.c.j2", ".c"), ("module.h.j2", ".h")):
            template = environment.get_template(template_name)
            output_path = output_dir / f"{module}{suffix}"
            output_path.write_text(template.render(context), encoding="utf-8", newline="\n")
            print(f"Generated {output_path}")


if __name__ == "__main__":
    main()
