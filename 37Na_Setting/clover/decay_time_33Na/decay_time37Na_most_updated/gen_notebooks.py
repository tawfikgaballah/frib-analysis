# gen_notebooks.py
# Create two Jupyter notebooks:
#  1) Modified_Bateman_PyMC.ipynb  — Modified Bateman (Dreher) + PyMC (generic Op)
#  2) Modified_Bateman_vs_CRAM_Toggle.ipynb — Toggle between Modified Bateman and CRAM-16, plus NUTS-capable model
#
# Usage:
#   python gen_notebooks.py
#
# Dependencies to RUN the notebooks later: numpy, pandas, matplotlib, pymc, aesara, arviz (optional for PPC plots).
# This script itself only needs nbformat (pip install nbformat).

import nbformat as nbf
from textwrap import dedent
from pathlib import Path

def write_notebook_bateman_pyMC(path: Path):
    nb = nbf.v4.new_notebook()
    cells = []

    cells.append(nbf.v4.new_markdown_cell(dedent("""
    # Modified Bateman (Dreher) + PyMC Integration
    This notebook provides:
    - A **modified Bateman** closed-form solution (after R. Dreher) that is robust for equal/near-equal half-lives and includes branching.
    - A demo (As-60 chain) with a plot and CSV export.
    - A **PyMC** model builder that uses the modified Bateman solution to compute **expected counts per time bin** with a **Poisson** likelihood and **softmax** branching ratios.

    Notes:
    - Times in **seconds**; background is a **rate** in counts/second.
    - Sampling cell is commented to avoid long runs by default.
    """)))

    cells.append(nbf.v4.new_code_cell(dedent("""
    import numpy as np
    import pandas as pd
    import matplotlib.pyplot as plt

    import pymc as pm
    import aesara
    import aesara.tensor as at

    %matplotlib inline
    plt.rcParams["figure.figsize"] = (8,5)
    LN2 = np.log(2.0)
    """)))

    cells.append(nbf.v4.new_markdown_cell("## Modified Bateman (Dreher) — general solver"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    from math import isfinite, factorial

    def modified_bateman_populations_at_times(times, T, R, N0):
        \"\"\"General Dreher 'modified Bateman' for a linear chain: times -> populations.
        T: [T1, T2, ...] half-lives (s), R: [R1, R2, ...] branch factors on each link.
        Returns array shape (len(times), ncols) with column 0 = t, columns 1.. = N_i(t).
        \"\"\"
        T = [0.0] + list(T)   # 1-based
        R = [0.0] + list(R)
        # chain length
        nn = 1
        for idx in range(1, len(T)):
            if T[idx] == 0: break
            nn = idx + 1
        # decay constants
        k = [0.0]*nn
        for i in range(1, nn):
            if T[i] > 1e99 or not isfinite(T[i]): k[i] = 0.0
            else: k[i] = LN2 / T[i]

        times = np.asarray(times, dtype=float)
        nt = len(times)
        out = np.zeros((nt, nn), dtype=float)
        out[:,0] = times

        for i in range(1, nn):
            # distinct lambdas up to i
            kd = []
            mult = []
            for qi in range(1, i+1):
                lam = k[qi]
                merged = False
                for j in range(len(kd)):
                    if abs(kd[j]-lam) <= 1e-15*max(1.0,abs(kd[j]),abs(lam)):
                        mult[j]+=1; merged=True; break
                if not merged:
                    kd.append(lam); mult.append(1)
            me = len(kd)

            # front factor N0 * Π R[j]*λ[j]
            Nbr = N0
            for j in range(1, i):
                Nbr *= R[j] * (LN2/T[j] if (T[j] < 1e99 and isfinite(T[j])) else 0.0)

            for j in range(me):
                # build V[0..mult[j]-1] via Leibniz sums
                V = [0.0]*mult[j]
                denom_inv = 1.0
                for p in range(me):
                    if p!=j: denom_inv /= (kd[p]-kd[j])**mult[p]
                V[0] = denom_inv
                for m in range(1, mult[j]):
                    S_acc = 0.0
                    for h in range(m):
                        S = 0.0
                        for p in range(me):
                            if p!=j: S += mult[p]/(kd[p]-kd[j])**(h+1)
                        S_acc += V[m-1-h]*S / factorial(m-1-h)
                    V[m] = S_acc*factorial(m-1)
                sign = -1 if (mult[j]-1)%2==1 else 1

                for it, tt in enumerate(times):
                    S = 0.0
                    for m in range(mult[j]):
                        S += V[m]*((-tt)**(mult[j]-1-m))/(factorial(mult[j]-1-m)*factorial(m))
                    out[it,i] += S*np.exp(-kd[j]*tt)*sign
            out[:,i] *= Nbr
        return out  # [t, N1, N2, ...]
    """)))

    cells.append(nbf.v4.new_markdown_cell("## Demo: As-60 chain"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    # Parse CLI-like inputs (e.g., "half[/branch]")
    def parse_cli_args_like(arg_list):
        T, R = [], []
        for s in arg_list:
            if "/" in s:
                t_str, r_str = s.split("/", 1)
                T.append(float(t_str)); R.append(float(r_str))
            else:
                T.append(float(s)); R.append(1.0)
        return T, R

    demo_args = ["1e-9", "1e-9", "0.038/0.35", "0.2", "129600", "23328000", "9e99"]
    T_demo, R_demo = parse_cli_args_like(demo_args)

    parent_T = T_demo[0]
    tmax = 10 * parent_T if np.isfinite(parent_T) and parent_T < 1e99 else 1.0
    times = np.linspace(0, tmax, 200)

    N0 = 6.022e23
    M = modified_bateman_populations_at_times(times, T_demo, R_demo, N0)

    for i in range(1, M.shape[1]):
        plt.plot(times, M[:, i], label=f"N{i}")
    plt.xlabel("Time (s)")
    plt.ylabel("Number of atoms")
    plt.title("Modified Bateman (Dreher) — Populations over Time")
    plt.legend(); plt.show()

    df = pd.DataFrame(M, columns=[f"N{i}" if i>0 else "time_s" for i in range(M.shape[1])])
    df.to_csv("modified_bateman_demo.csv", index=False)
    print("Saved: modified_bateman_demo.csv")
    """)))

    cells.append(nbf.v4.new_markdown_cell("## Expected activity and binned counts"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    def total_activity_parent_only(times, parent_half_life, N0):
        lam = np.log(2.0) / parent_half_life
        N_parent = N0 * np.exp(-lam * times)
        return lam * N_parent  # A_parent(t)

    def total_activity_with_branches(times, A0, parentT, d0, d1, d2, b_vec, include_parent=True):
        times = np.asarray(times, dtype=float)
        A_total = np.zeros_like(times, dtype=float)
        if include_parent:
            lam_p = np.log(2.0) / parentT
            A_total += lam_p * A0 * np.exp(-lam_p * times)
        for key, Td in daughTs.items():
            b = b_vec.get(key, 0.0)
            if b <= 0: continue
            T = [parentT, Td]; R = [1.0, b]
            M = modified_bateman_populations_at_times(times, T, R, N0=A0)
            lam_d = np.log(2.0) / Td
            A_total += lam_d * M[:, 2]
        return A_total

    def expected_counts_per_bin(times_center_s, bin_width_s, A0, parentT, daughTs, b_vec,
                                background_rate=0.0, oversample_factor=1):
        times_center_s = np.asarray(times_center_s, dtype=float)
        dt = float(bin_width_s)
        if oversample_factor <= 1:
            A_mid = total_activity_with_branches(times_center_s, A0, parentT, daughTs, b_vec, include_parent=True)
            return A_mid * dt + background_rate * dt
        nb = len(times_center_s)
        lam_counts = np.zeros(nb, dtype=float)
        sub = oversample_factor
        for i, tc in enumerate(times_center_s):
            t0 = tc - 0.5 * dt; t1 = tc + 0.5 * dt
            ts = np.linspace(t0, t1, sub + 1)
            A_sub = total_activity_with_branches(ts, A0, parentT, daughTs, b_vec, include_parent=True)
            lam_counts[i] = np.trapz(A_sub, ts) + background_rate * dt
        return lam_counts
    """)))

    cells.append(nbf.v4.new_markdown_cell("## PyMC model builder (generic Op; use Slice/Metropolis)"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    from aesara.graph.op import Op

    class ExpectedCountsOp(Op):
        itypes = [aesara.tensor.dvector, aesara.tensor.dscalar,  # centers, width
                  aesara.tensor.dscalar, aesara.tensor.dscalar,  # A0, parentT
                  aesara.tensor.dscalar, aesara.tensor.dscalar, aesara.tensor.dscalar,  # d0,d1,d2
                  aesara.tensor.dvector,  # b
                  aesara.tensor.dscalar]  # bg
        otypes = [aesara.tensor.dvector]
        def perform(self, node, inputs, outputs):
            centers, width, A0_, parentT_, d0_, d1_, d2_, b_arr, bg_ = inputs
            lam = expected_counts_per_bin(
                centers, float(width), float(A0_), float(parentT_),
                {"0n": float(d0_), "1n": float(d1_), "2n": float(d2_)},
                {"0n": float(b_arr[0]), "1n": float(b_arr[1]), "2n": float(b_arr[2])},
                background_rate=float(bg_), oversample_factor=1
            )
            outputs[0][0] = lam.astype(np.float64)

    def build_bateman_pymc_model(bin_centers_s=None, bin_edges_s=None, bin_width_s=None, y_counts=None,
                                 priors=None):
        if bin_edges_s is not None:
            edges = np.asarray(bin_edges_s, dtype=float)
            centers = 0.5 * (edges[:-1] + edges[1:])
            width = (edges[1] - edges[0])
        else:
            assert bin_centers_s is not None and bin_width_s is not None, "Provide edges OR (centers & width)."
            centers = np.asarray(bin_centers_s, dtype=float)
            width = float(bin_width_s)
        assert y_counts is not None, "Provide observed counts per bin."
        y = np.asarray(y_counts, dtype=int)
        assert len(y) == len(centers), "y_counts length must match number of bins."

        priors = priors or {}
        with pm.Model() as model:
            A0 = pm.HalfNormal("A0", sigma=priors.get("A0_sigma", 1e25))
            parentT = pm.LogNormal("parentT", mu=np.log(priors.get("parentT_mu", 0.01)), sigma=priors.get("parentT_sigma", 2.0))
            d0 = pm.LogNormal("daugh0nT", mu=np.log(priors.get("d0_mu", 0.01)), sigma=priors.get("d0_sigma", 1.0))
            d1 = pm.LogNormal("daugh1nT", mu=np.log(priors.get("d1_mu", 0.01)), sigma=priors.get("d1_sigma", 1.0))
            d2 = pm.LogNormal("daugh2nT", mu=np.log(priors.get("d2_mu", 0.01)), sigma=priors.get("d2_sigma", 1.0))

            logits = pm.Normal("logits", mu=priors.get("logits_mu", 0.0), sigma=priors.get("logits_sigma", 1.0), shape=3)
            b = pm.Deterministic("b", at.nnet.softmax(logits))

            bg = pm.HalfNormal("backgroundRate", sigma=priors.get("bg_sigma", 1e4))

            centers_data = pm.MutableData("bin_centers_s", centers)
            width_data   = pm.MutableData("bin_width_s", np.array(width, dtype=float))

            exp_counts = ExpectedCountsOp()(centers_data, width_data, A0, parentT, d0, d1, d2, b, bg)
            y_obs = pm.Poisson("y_obs", mu=exp_counts, observed=y)

        return model
    """)))

    cells.append(nbf.v4.new_markdown_cell("## Quick synthetic test (replace with your real data)"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    # 1 ms bins from 0..200 ms
    bin_centers_ms = np.arange(0.5, 200.5, 1.0)
    bin_width_ms = 1.0
    bin_centers_s = bin_centers_ms * 1e-3
    bin_width_s = bin_width_ms * 1e-3

    true = dict(A0=1e10, parentT=0.040, d0=0.0064, d1=0.0072, d2=0.0114,
                b0=0.00, b1=0.51, b2=0.24, bg=5.0)
    b_vec_true = {"0n": true["b0"], "1n": true["b1"], "2n": true["b2"]}
    daughTs_true = {"0n": true["d0"], "1n": true["d1"], "2n": true["d2"]}
    lam_true = expected_counts_per_bin(bin_centers_s, bin_width_s, true["A0"], true["parentT"],
                                       daughTs_true, b_vec_true, background_rate=true["bg"], oversample_factor=1)
    rng = np.random.default_rng(4)
    y_counts = rng.poisson(lam_true)

    priors = dict(
        A0_sigma=1e11,
        parentT_mu=0.05, parentT_sigma=1.0,
        d0_mu=0.0064, d0_sigma=0.5,
        d1_mu=0.0072, d1_sigma=0.5,
        d2_mu=0.0114, d2_sigma=0.5,
        logits_mu=0.0, logits_sigma=2.0,
        bg_sigma=100.0
    )

    model = build_bateman_pymc_model(bin_centers_s=bin_centers_s, bin_width_s=bin_width_s,
                                     y_counts=y_counts, priors=priors)
    model
    """)))

    cells.append(nbf.v4.new_markdown_cell("## Sampling (uncomment to run)"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    # with model:
    #     idata = pm.sample(2000, tune=1000, target_accept=0.9, chains=4, cores=1,
    #                       step=pm.Slice(), random_seed=42)
    # idata
    """)))

    nb.cells = cells
    path.write_text(nbf.writes(nb), encoding="utf-8")


def write_notebook_toggle_toggle(path: Path):
    nb = nbf.v4.new_notebook()
    cells = []

    cells.append(nbf.v4.new_markdown_cell(dedent("""
    # Modified Bateman vs CRAM-16 — Toggleable Engines (with PyMC)
    - `expected_counts_per_bin(..., engine="bateman"|"cram")` to switch engines.
    - **CRAM-16** (Chebyshev Rational Approximation) for matrix exponentials.
    - **Modified Bateman** engine and a **symbolic Bateman** (NUTS-capable).
    - Two PyMC model builders:
      - `build_model_symbolic_bateman_nuts(...)`
      - `build_model_generic_op(..., engine=...)` (Slice/Metropolis)
    """)))

    cells.append(nbf.v4.new_code_cell(dedent("""
    import numpy as np
    import pandas as pd
    import matplotlib.pyplot as plt

    import pymc as pm
    import aesara
    import aesara.tensor as at

    %matplotlib inline
    plt.rcParams["figure.figsize"] = (8,5)
    LN2 = np.log(2.0)
    """)))

    cells.append(nbf.v4.new_markdown_cell("## Modified Bateman — engine"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    from math import isfinite, factorial

    def modified_bateman_populations_at_times(times, T, R, N0):
        T = [0.0] + list(T)
        R = [0.0] + list(R)
        nn = 1
        for idx in range(1, len(T)):
            if T[idx] == 0: break
            nn = idx + 1
        k = [0.0]*nn
        for i in range(1, nn):
            if T[i] > 1e99 or not isfinite(T[i]): k[i] = 0.0
            else: k[i] = LN2 / T[i]
        times = np.asarray(times, dtype=float)
        out = np.zeros((len(times), nn), dtype=float); out[:,0] = times
        for i in range(1, nn):
            kd, mult = [], []
            for qi in range(1, i+1):
                lam = k[qi]
                merged=False
                for j in range(len(kd)):
                    if abs(kd[j]-lam) <= 1e-15*max(1.0,abs(kd[j]),abs(lam)):
                        mult[j]+=1; merged=True; break
                if not merged: kd.append(lam); mult.append(1)
            me = len(kd)
            Nbr = 6.022e23
            for j in range(1, i):
                Nbr *= R[j] * (LN2/T[j] if (T[j] < 1e99 and isfinite(T[j])) else 0.0)
            for j in range(me):
                V = [0.0]*mult[j]
                denom_inv = 1.0
                for p in range(me):
                    if p!=j: denom_inv /= (kd[p]-kd[j])**mult[p]
                V[0] = denom_inv
                for m in range(1, mult[j]):
                    S_acc = 0.0
                    for h in range(m):
                        S = 0.0
                        for p in range(me):
                            if p!=j: S += mult[p]/(kd[p]-kd[j])**(h+1)
                        S_acc += V[m-1-h]*S / factorial(m-1-h)
                    V[m] = S_acc*factorial(m-1)
                sign = -1 if (mult[j]-1)%2==1 else 1
                for it, tt in enumerate(times):
                    S = 0.0
                    for m in range(mult[j]):
                        S += V[m]*((-tt)**(mult[j]-1-m))/(factorial(mult[j]-1-m)*factorial(m))
                    out[it,i] += S*np.exp(-kd[j]*tt)*sign
            out[:,i] *= Nbr
        return out

    def total_activity_bateman_parent_plus_daughters(times, A0, parentT, d0, d1, d2, b_vec, include_parent=True):
        t = np.asarray(times, dtype=float)
        lam_p = LN2/parentT; lam0 = LN2/d0; lam1 = LN2/d1; lam2 = LN2/d2
        A = np.zeros_like(t, dtype=float)
        if include_parent:
            A += lam_p * A0 * np.exp(-lam_p*t)
        for lam_d, Td, b in zip([lam0,lam1,lam2],[d0,d1,d2], b_vec):
            if b <= 0: continue
            delta = lam_d - lam_p
            common = np.exp(-lam_p*t) - np.exp(-lam_d*t)
            expr = A0*b*lam_d*(lam_p/delta)*common
            expr_lim = A0*b*(lam_p**2)*t*np.exp(-lam_p*t)
            A += np.where(np.abs(delta)<1e-12, expr_lim, expr)
        return A

    def expected_counts_per_bin_bateman(centers_s, bin_width_s, A0, parentT, d0, d1, d2, b_vec,
                                        background_rate=0.0, oversample=1):
        c = np.asarray(centers_s, dtype=float); dt = float(bin_width_s)
        if oversample<=1:
            rate = total_activity_bateman_parent_plus_daughters(c, A0,parentT,d0,d1,d2,b_vec, True) + background_rate
            return rate*dt
        out = np.empty_like(c)
        for i, tc in enumerate(c):
            t0, t1 = tc-0.5*dt, tc+0.5*dt
            ts = np.linspace(t0, t1, oversample+1)
            rate = total_activity_bateman_parent_plus_daughters(ts, A0,parentT,d0,d1,d2,b_vec, True) + background_rate
            out[i] = np.trapz(rate, ts)
        return out
    """)))

    cells.append(nbf.v4.new_markdown_cell("## CRAM-16 — engine"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    theta = np.array([
        -1.0843917078696988026e+01 + 1.9277446167181652284e+01j,
        -5.2649713434426468895e+00 + 1.6220221473167927305e+01j,
         5.9481522689511774808e+00 + 3.5874573620183222829e+00j,
         3.5091036084149180974e+00 + 8.4361989858843750826e+00j,
         6.4161776990994341923e+00 + 1.1941223933701386874e+00j,
         1.4193758971856659786e+00 + 1.0925363484496722585e+01j,
         4.9931747377179963991e+00 + 5.9968817136039422260e+00j,
        -1.4139284624888862114e+00 + 1.3497725698892745389e+01j
    ], dtype=np.complex128)

    alpha = np.array([
        -5.0901521865224915650e-07 - 2.4220017652852287970e-05j,
         2.1151742182466030907e-04 + 4.3892969647380673918e-03j,
         1.1339775178483930527e+02 + 1.0194721704215856450e+02j,
         1.5059585270023467528e+01 - 5.7514052776421819979e+00j,
        -6.4500878025539646595e+01 - 2.2459440762652096056e+02j,
        -1.4793007113557999718e+00 + 1.7686588323782937906e+00j,
        -6.2518392463207918892e+01 - 1.1190391094283228480e+01j,
         4.1023136835410021273e-02 - 1.5743466173455468191e-01j
    ], dtype=np.complex128)

    alpha0 = 2.1248537104952237488e-16

    def cram16_expm_action(A, t, x0):
        n = A.shape[0]
        M = (A*t).astype(np.complex128, copy=False)
        I = np.eye(n, dtype=np.complex128)
        y = alpha0 * x0.astype(np.complex128)
        for th, al in zip(theta, alpha):
            yj = np.linalg.solve(M - th*I, x0)
            y += 2.0*np.real(al * yj)
        return np.real(y)

    def decay_matrix_parent_3daughters(parentT, d0, d1, d2, b_vec):
        lam_p = LN2/parentT; lam0 = LN2/d0; lam1 = LN2/d1; lam2 = LN2/d2
        b0,b1,b2 = b_vec
        A = np.array([
            [-lam_p,    0.0,    0.0,    0.0],
            [ b0*lam_p,-lam0,   0.0,    0.0],
            [ b1*lam_p, 0.0,  -lam1,    0.0],
            [ b2*lam_p, 0.0,    0.0,  -lam2],
        ], dtype=float)
        return A, lam_p, lam0, lam1, lam2

    def expected_counts_per_bin_cram(centers_s, bin_width_s, A0, parentT, d0, d1, d2, b_vec,
                                     background_rate=0.0, oversample=1):
        A, lam_p, lam0, lam1, lam2 = decay_matrix_parent_3daughters(parentT, d0, d1, d2, b_vec)
        c = np.asarray(centers_s, dtype=float); dt = float(bin_width_s)
        out = np.empty_like(c)
        x0 = np.array([A0,0,0,0], dtype=float)
        if oversample<=1:
            for i, t in enumerate(c):
                N = cram16_expm_action(A, t, x0)
                rate = lam_p*N[0] + lam0*N[1] + lam1*N[2] + lam2*N[3] + background_rate
                out[i] = rate*dt
            return out
        for i, tc in enumerate(c):
            t0, t1 = tc-0.5*dt, tc+0.5*dt
            ts = np.linspace(t0, t1, oversample+1)
            rates = []
            for t in ts:
                N = cram16_expm_action(A, t, x0)
                rate = lam_p*N[0] + lam0*N[1] + lam1*N[2] + lam2*N[3] + background_rate
                rates.append(rate)
            out[i] = np.trapz(rates, ts)
        return out
    """)))

    cells.append(nbf.v4.new_markdown_cell("## Unified wrapper"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    def expected_counts_per_bin(centers_s, bin_width_s, A0, parentT, d0, d1, d2, b_vec,
                                background_rate=0.0, oversample=1, engine="bateman"):
        engine = engine.lower()
        if engine == "bateman":
            return expected_counts_per_bin_bateman(centers_s, bin_width_s, A0,parentT,d0,d1,d2,b_vec,
                                                   background_rate=background_rate, oversample=oversample)
        elif engine == "cram":
            return expected_counts_per_bin_cram(centers_s, bin_width_s, A0,parentT,d0,d1,d2,b_vec,
                                                background_rate=background_rate, oversample=oversample)
        else:
            raise ValueError("engine must be 'bateman' or 'cram'")
    """)))

    cells.append(nbf.v4.new_markdown_cell("## PyMC model (NUTS-friendly) — symbolic Bateman"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    def _daughter_activity_symbolic(t, A0, b, lam_p, lam_d):
        delta = lam_d - lam_p
        common = at.exp(-lam_p*t) - at.exp(-lam_d*t)
        expr     = A0 * b * lam_d * (lam_p/delta) * common
        expr_lim = A0 * b * (lam_p**2) * t * at.exp(-lam_p*t)
        return at.switch(at.abs_(delta) < 1e-12, expr_lim, expr)

    def expected_counts_symbolic_bateman(centers_s, width_s, A0, parentT, d0, d1, d2, b_vec, bg_rate):
        t = centers_s
        lam_p = LN2/parentT; lam0 = LN2/d0; lam1 = LN2/d1; lam2 = LN2/d2
        A_parent = lam_p * A0 * at.exp(-lam_p*t)
        A_0n = _daughter_activity_symbolic(t, A0, b_vec[0], lam_p, lam0)
        A_1n = _daughter_activity_symbolic(t, A0, b_vec[1], lam_p, lam1)
        A_2n = _daughter_activity_symbolic(t, A0, b_vec[2], lam_p, lam2)
        A_total = A_parent + A_0n + A_1n + A_2n + bg_rate
        return A_total * width_s

    def build_model_symbolic_bateman_nuts(bin_centers_s, bin_width_s, y_counts, priors=None):
        priors = priors or {}
        c = at.as_tensor_variable(np.asarray(bin_centers_s, dtype=float))
        w = float(bin_width_s)
        y = np.asarray(y_counts, dtype=int)

        with pm.Model() as model:
            A0 = pm.HalfNormal("A0", sigma=priors.get("A0_sigma", 1e10))
            parentT = pm.LogNormal("parentT", mu=np.log(priors.get("parentT_mu", 0.008)), sigma=priors.get("parentT_sigma", 0.5))
            d0 = pm.LogNormal("daugh0nT", mu=np.log(priors.get("d0_mu", 0.0064)), sigma=priors.get("d0_sigma", 0.2))
            d1 = pm.LogNormal("daugh1nT", mu=np.log(priors.get("d1_mu", 0.0072)), sigma=priors.get("d1_sigma", 0.2))
            d2 = pm.LogNormal("daugh2nT", mu=np.log(priors.get("d2_mu", 0.0114)), sigma=priors.get("d2_sigma", 0.2))

            logits = pm.Normal("logits", mu=priors.get("logits_mu", 0.0), sigma=priors.get("logits_sigma", 2.0), shape=3)
            b = pm.Deterministic("b", at.nnet.softmax(logits))

            bg = pm.HalfNormal("backgroundRate", sigma=priors.get("bg_sigma", 1e6))

            mu = expected_counts_symbolic_bateman(c, w, A0, parentT, d0, d1, d2, b, bg)
            y_obs = pm.Poisson("y_obs", mu=mu, observed=y)
        return model
    """)))

    cells.append(nbf.v4.new_markdown_cell("## PyMC model (generic Op) — choose engine='bateman' or 'cram'"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    from aesara.graph.op import Op

    class ExpectedCountsOp(Op):
        itypes = [aesara.tensor.dvector, aesara.tensor.dscalar,  # centers, width
                  aesara.tensor.dscalar, aesara.tensor.dscalar,  # A0, parentT
                  aesara.tensor.dscalar, aesara.tensor.dscalar, aesara.tensor.dscalar,  # d0,d1,d2
                  aesara.tensor.dvector,  # b
                  aesara.tensor.dscalar]  # bg
        otypes = [aesara.tensor.dvector]
        def __init__(self, engine="bateman"):
            self.engine = engine
            super().__init__()
        def perform(self, node, inputs, outputs):
            centers, width, A0_, parentT_, d0_, d1_, d2_, b_arr, bg_ = inputs
            lam = expected_counts_per_bin(
                centers, float(width), float(A0_), float(parentT_), float(d0_), float(d1_), float(d2_),
                np.array([float(b_arr[0]), float(b_arr[1]), float(b_arr[2])], dtype=float),
                background_rate=float(bg_), oversample=1, engine=self.engine
            )
            outputs[0][0] = lam.astype(np.float64)

    def build_model_generic_op(bin_centers_s, bin_width_s, y_counts, priors=None, engine="bateman"):
        priors = priors or {}
        centers = np.asarray(bin_centers_s, dtype=float)
        width = float(bin_width_s)
        y = np.asarray(y_counts, dtype=int)

        with pm.Model() as model:
            A0 = pm.HalfNormal("A0", sigma=priors.get("A0_sigma", 1e10))
            parentT = pm.LogNormal("parentT", mu=np.log(priors.get("parentT_mu", 0.008)), sigma=priors.get("parentT_sigma", 0.5))
            d0 = pm.LogNormal("daugh0nT", mu=np.log(priors.get("d0_mu", 0.0064)), sigma=priors.get("d0_sigma", 0.2))
            d1 = pm.LogNormal("daugh1nT", mu=np.log(priors.get("d1_mu", 0.0072)), sigma=priors.get("d1_sigma", 0.2))
            d2 = pm.LogNormal("daugh2nT", mu=np.log(priors.get("d2_mu", 0.0114)), sigma=priors.get("d2_sigma", 0.2))

            logits = pm.Normal("logits", mu=priors.get("logits_mu", 0.0), sigma=priors.get("logits_sigma", 2.0), shape=3)
            b = pm.Deterministic("b", at.nnet.softmax(logits))

            bg = pm.HalfNormal("backgroundRate", sigma=priors.get("bg_sigma", 1e6))

            centers_data = pm.MutableData("bin_centers_s", centers)
            width_data   = pm.MutableData("bin_width_s", np.array(width, dtype=float))

            exp_counts = ExpectedCountsOp(engine=engine)(centers_data, width_data, A0, parentT, d0, d1, d2, b, bg)
            y_obs = pm.Poisson("y_obs", mu=exp_counts, observed=y)
        return model
    """)))

    cells.append(nbf.v4.new_markdown_cell("## Synthetic demo + engine comparison"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    # Synthetic data: 1 ms bins, 0..200 ms
    bin_centers_ms = np.arange(0.5, 200.5, 1.0)
    bin_width_ms = 1.0
    bin_centers_s = bin_centers_ms * 1e-3
    bin_width_s   = bin_width_ms * 1e-3

    true = dict(A0=1e10, parentT=0.040, d0=0.0064, d1=0.0072, d2=0.0114, b0=0.00, b1=0.51, b2=0.24, bg=5.0)
    b_vec_true = np.array([true["b0"], true["b1"], true["b2"]], dtype=float)

    lam_bateman = expected_counts_per_bin(bin_centers_s, bin_width_s, true["A0"], true["parentT"],
                                          true["d0"], true["d1"], true["d2"], b_vec_true,
                                          background_rate=true["bg"], engine="bateman")
    lam_cram    = expected_counts_per_bin(bin_centers_s, bin_width_s, true["A0"], true["parentT"],
                                          true["d0"], true["d1"], true["d2"], b_vec_true,
                                          background_rate=true["bg"], engine="cram")

    plt.plot(bin_centers_ms, lam_bateman, label="Bateman expected counts")
    plt.plot(bin_centers_ms, lam_cram, "--", label="CRAM-16 expected counts")
    plt.xlabel("time (ms)"); plt.ylabel("expected counts / bin"); plt.title("Engines comparison")
    plt.legend(); plt.show()

    rng = np.random.default_rng(7)
    y_counts = rng.poisson(lam_bateman)

    priors = dict(
        A0_sigma=1e11,
        parentT_mu=0.05, parentT_sigma=0.6,
        d0_mu=0.0064, d0_sigma=0.2,
        d1_mu=0.0072, d1_sigma=0.2,
        d2_mu=0.0114, d2_sigma=0.2,
        logits_mu=0.0, logits_sigma=2.0,
        bg_sigma=100.0
    )
    """)))

    cells.append(nbf.v4.new_markdown_cell("### Sample with NUTS (symbolic Bateman) — uncomment to run"))
    cells.append(nbf.v4.new_code_cell(dedent("""
    # model_nuts = build_model_symbolic_bateman_nuts(bin_centers_s, bin_width_s, y_counts, priors=priors)
    # with model_nuts:
    #     idata_nuts = pm.sample(2000, tune=1000, target_accept=0.95, chains=4, cores=4, random_seed=42)
    # idata_nuts
    """)))

    cells.append(nbf.v4.new_markdown_cell('### Sample with Slice/Metropolis (generic Op) — engine="bateman" or "cram"'))
    cells.append(nbf.v4.new_code_cell(dedent("""
    # engine_choice = "cram"   # or "bateman"
    # model_op = build_model_generic_op(bin_centers_s, bin_width_s, y_counts, priors=priors, engine=engine_choice)
    # with model_op:
    #     idata_op = pm.sample(2000, tune=1000, chains=4, cores=1, step=pm.Slice(), random_seed=42)
    # idata_op
    """)))

    nb.cells = cells
    path.write_text(nbf.writes(nb), encoding="utf-8")


def main():
    out1 = Path("Modified_Bateman_PyMC.ipynb")
    out2 = Path("Modified_Bateman_vs_CRAM_Toggle.ipynb")
    write_notebook_bateman_pyMC(out1)
    write_notebook_toggle_toggle(out2)
    print(f"Created: {out1.resolve()}")
    print(f"Created: {out2.resolve()}")
    print("\nOpen them in Jupyter/Lab/VSCode. If you need a single .py script version instead of notebooks, say the word.")

if __name__ == "__main__":
    main()
