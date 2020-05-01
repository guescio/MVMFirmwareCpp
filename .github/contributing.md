***This is a draft and it needs to be expanded.***

# Change request workflow #

This is a summary description of the workflow to handle Change Requests (CRs) and it should be used as a quick reference.


## Submission ##

Submission of any issues should be done by anyone by filling in the information requested in the [change request template](https://github.com/guescio/MVMFirmwareCpp/blob/master/.github/ISSUE_TEMPLATE/change-request.md).

Remember to **add the labels** that better suit the CR being submitted, e.g.: `firmware`, `GUI`, `regulatory request` or `high priority`.

Do **not** alter the `change request` and `pending approval` labels added by default.

Add the issue to the `MVM SQA` **project** in the `pending review` tab.

In the following steps, the CR will be reviewed and processed.


## Review ##

Reviewers (automatically added in the previous step) have the role of approving or rejecting a CR. This is done by applying the appropriate flag and by moving the issue to either the `to do` or `rejected` column in the GitHub Project.


## Implementation ##

Developers in charge of the affected areas (Firmware, GUI etc.) take care of implementing the CR. This is done by making a private fork of the repository and then submitting a Pull Request (PR) with the modifications.

PRs have a dedicated template and it should be specified therein what is the issues number these refer to.

While CRs are being implemented, the corresponding issue should be moved to the `in progress` tab of the GitHub project.

Once the implementation is completed, the `pending validation` label should be applied and the issue moved to the `validating` column in the GitHub project.


## Validation ##

Before the PR is completed, the CR needs to be reviewed and validated.

Once the PR is validated and finally merged, the label `pending test` should be added and the issue moved to the `integration testing` column of the GitHub project.

If the CR does not pass validation, it should be moved back to `pending review`.


## Integration testing ##

This is where the integration tests of the updated branch happen.

If tests are successful, the CR is completed and it should be move to the `done` column of the GitHub project.

If a test fails, a new CR should be submitted.


## Rejection ##

If at any stage a CR is rejected, this should be moved to the `rejected` column of the GitHub project.
