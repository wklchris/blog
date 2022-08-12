require.config({
    paths: {
      "jquery": "_static/jquery",
      "datatables": "_static/DataTables/datatables.min"
    }
});
requirejs( ["datatables"], function () {
    $('#tableofblogs').DataTable( {
      language: {
          url: "_static/DataTables/zh_CN.json" 
      } 
    } );
} );