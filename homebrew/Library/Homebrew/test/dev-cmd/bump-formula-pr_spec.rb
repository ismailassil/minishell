# frozen_string_literal: true

require "cmd/shared_examples/args_parse"

RSpec.describe "brew bump-formula-pr" do
  it_behaves_like "parseable arguments"
end
