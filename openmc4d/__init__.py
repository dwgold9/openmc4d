import importlib.util
import pathlib
import sys

# Path to the sibling openmc directory
_openmc_path = pathlib.Path(__file__).resolve().parent.parent / "openmc"

# Add to sys.path if not already there
if str(_openmc_path.parent) not in sys.path:
    sys.path.insert(0, str(_openmc_path.parent))

import openmc as _openmc

__version__ = "0.15.3-4d"

def __getattr__(name):
    return getattr(_openmc, name)

def __dir__():
    return sorted(list(globals().keys()) + dir(_openmc))

# --- key lines for subpackages: mirror search path/spec ---
# Make 'openmc4d' a package whose search locations are the same as 'openmc'
__path__ = _openmc.__path__  # so 'openmc4d.mgxs' resolves to <openmc>/mgxs.py
try:
    # Keep importlib happy for namespace discovery
    __spec__.submodule_search_locations = list(_openmc.__spec__.submodule_search_locations)  # type: ignore[attr-defined]
except Exception:
    pass

# Optional: lazy aliasing of submodules when accessed as attributes
def __getattr__(name):
    try:
        return getattr(_openmc, name)
    except AttributeError:
        # If someone does: openmc4d.mgxs (as attribute), import it from openmc and alias
        mod = importlib.import_module(f"openmc.{name}")
        sys.modules[f"{__name__}.{name}"] = mod
        return mod