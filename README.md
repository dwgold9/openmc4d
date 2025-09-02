# OpenMC4d

[![License](https://img.shields.io/badge/license-MIT-green)](https://docs.openmc.org/en/latest/license.html)
[![GitHub Actions build status (Linux)](https://github.com/openmc-dev/openmc/actions/workflows/ci.yml/badge.svg?branch=develop)](https://github.com/openmc-dev/openmc/actions/workflows/ci.yml)
[![Code Coverage](https://coveralls.io/repos/github/openmc-dev/openmc/badge.svg?branch=develop)](https://coveralls.io/github/openmc-dev/openmc?branch=develop)
[![dockerhub-publish-develop-dagmc](https://github.com/openmc-dev/openmc/workflows/dockerhub-publish-develop-dagmc/badge.svg)](https://github.com/openmc-dev/openmc/actions?query=workflow%3Adockerhub-publish-develop-dagmc)
[![dockerhub-publish-develop](https://github.com/openmc-dev/openmc/workflows/dockerhub-publish-develop/badge.svg)](https://github.com/openmc-dev/openmc/actions?query=workflow%3Adockerhub-publish-develop)
[![conda-pacakge](https://anaconda.org/conda-forge/openmc/badges/version.svg)](https://anaconda.org/conda-forge/openmc)

openmc4d is a custom research fork of [OpenMC](https://github.com/openmc-dev/openmc) that extends the Monte Carlo particle transport framework into an additional temporal dimension. It is designed for time-structured neutronics (TSN) studies, where reactor systems alternate between distinct subcritical configurations in time.

## Key Features

- **4D Geometry Surfaces**  
  New time-dependent surfaces (e.g., `TPlane`) for defining regions and material boundaries that evolve in time.  

- **Dynamic Material and Operator Support**  
  Ability to modulate material properties, cross sections, and source terms over specified temporal intervals.  

- **Floquet / Periodic Analyses**  
  Tools for evaluating reactivity gain, α-eigenvalues, and mode structures in systems under periodic modulation.  

- **Python and YAML Interface**  
  Python bindings and YAML-driven inputs extend existing OpenMC workflows for defining 4D problems reproducibly.  

- **Backward Compatibility**  
  Standard 3D OpenMC simulations remain supported, with 4D functionality activated via the `OPENMC_ENABLE_4D` build option.  

## Research Applications

- Proof-of-principle studies in time-structured reactor design 
- Investigation of reactivity boosts in depleted-uranium / heavy-water systems  
- Exploration of dynamic isotope tailoring and spectral shaping  
- Modeling of conceptual designs such as Floquet microreactors  

## Getting Started

### Build Instructions

```bash
git clone https://github.com/dwgold9/openmc4d.git
cd openmc4d
mkdir build && cd build
cmake .. -DOPENMC_ENABLE_4D=on
make -j4


## License

OpenMC is distributed under the MIT/X
[license](https://docs.openmc.org/en/stable/license.html).
