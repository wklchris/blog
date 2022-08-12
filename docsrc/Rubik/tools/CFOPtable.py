import os
import pandas as pd

DIR = os.path.abspath(os.path.dirname(__file__))
cfop = pd.read_csv(os.path.join(DIR, "CFOP-method.csv"))

# Process roofpig
def solution_parser(rubik_solution):
    """Remove parens and insert spaces to solution strings."""
    alg = rubik_solution.replace("(", '').replace(")",'')
    alg = ' '.join(alg).replace(" 2", "2").replace(" '", "'")
    return alg

def alg_to_roofpig(alg, div_text="", dataconfig_paras=dict()):
    paras = {"flags": "", "algdisplay": "2p"}
    paras.update(dataconfig_paras)
    paras_str = '|'.join([k + "=" + v for k, v in paras.items() if v])
    
    dataconfig_str = f"alg={alg}|{paras_str}"
    div_str = f'<div class="roofpig" data-config="{dataconfig_str}">{div_text}</div>'
    return div_str

def process_html(df, type_filter, add_colgroup=True):
    df = df[df["type"] == type_filter]
    df.fillna('', inplace=True)

    html_linebreak = "<br />"
    # Integrate cols: type, id, and alias
    df["id_str"] = df["type"] + ' ' + df["id"].astype(str)
    df.insert(0, "id_str", df.pop("id_str"))
    df.loc[df["alias"] != '', "id_str"] = df.loc[df["alias"] != '', "id_str"] + html_linebreak + "(" + df.loc[df["alias"] != '', "alias"] + ")"
    # Integrate cols: comment with solution & observe
    df["comment"] = df["comment"] + html_linebreak + "<b>" + df["solution"] + "</b>"
    df.loc[df["observe"] != '', 'comment'] = df.loc[df["observe"] != '', 'comment'] + html_linebreak + "观察：" + df.loc[df["observe"] != '', 'observe']

    # Convert solution column to roofpig HTML codes
    df["solution"] = df["solution"].apply(
        lambda x: alg_to_roofpig(solution_parser(x))
    )

    df = df.drop(columns=["type", "id", "alias", "observe"])
    df_en_colnames = df.columns
    df.rename(columns={
        "id_str": "编号",
        "name": "名称",
        "group": "分组",
        "solution": "公式",
        "comment": "注解"
    }, inplace=True)

    html = df.to_html(
        classes="roofpig-table",
        # na_rep='',
        justify='center',
        escape=False,  # Keep HTML syntax for the solution column
        index=False
    )

    # Add <colgroup>
    if add_colgroup:
        colgroups = [f'    <col class="{col}" />' for col in df_en_colnames]
        colgroup_labels = "\n".join(colgroups)
        colgroup_str = "\n".join(["  <colgroup>", colgroup_labels, "  </colgroup>"])
        ## Add it to the second line of the HTML, right after <table>
        firstline, remain = html.split("\n", 1)
        html = "\n".join([firstline, colgroup_str, remain])

    return html

# Main

cfop_filter = 'PLL'
html_str = process_html(cfop, cfop_filter[:5])

with open(os.path.join(DIR, cfop_filter + '.html'), 'w', encoding="utf-8") as f:
    f.write(html_str)
